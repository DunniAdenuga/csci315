#include "read_dir.h"
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <unistd.h>

// function prototypes
void process(char *name);
void enqueue(char *name, que_t *q);
void dequeue(que_t *q);
void peek_front(char *name,que_t q);
bool queue_empty(que_t q);
void initq(que_t *q);

int main(int argc, char *argv[]){
if (2 != argc) {
    printf(" usage: %s dirpath\n", argv[0]);
    exit(-1);
  }
  else {
    // pass in the starting directory
    process(argv[1]);       
  }
  
  return 0;
}
// traverse a directory tree applying a function when a file is found
void process(char *root)
{
  int numOfFiles = 0;
  int numofDir = 0;
  int sFileSize = 0;
  int lFileSize = 0;
  int avgFileSize = 0;
  que_t nameq;
  char mostRecentFile[MAXLENGTH];
  char leastRecentFile[MAXLENGTH];
  char dname[MAXLENGTH];
  char cname[MAXLENGTH];
  char prefix[MAXLENGTH];
  time_t mostRecent;
  time_t leastRecent;

  struct dirent *dp;
  DIR *dirp;

    initq(&nameq);
    enqueue(root,&nameq);

    while (true != queue_empty(nameq)) {
      peek_front(dname,nameq); 
      dequeue(&nameq);
      
      dirp = opendir(dname);
       struct stat file;
       lstat(dname, &file);
       if(S_ISLNK(file.st_mode)){
	 printf("%s is a symbolic link of size %d.\n", dname, file.st_size); 
	 dirp = NULL;
	   }

      if (dirp != NULL) { // it is a directory
      
	numofDir++;
	printf("directory : %s\n",dname);
	strncpy(prefix, dname, MAXLENGTH);
	strncat(prefix,"/", MAXLENGTH);
	
	for (dp = readdir(dirp); NULL != dp; dp = readdir(dirp)) {
	  if ((strcmp(dp->d_name,"..") != 0) && 
	      (strcmp(dp->d_name,".") != 0)) {
	    
	    // prevent from infinite loop
	    strncpy(cname, prefix, MAXLENGTH);
	    
	    // concatenate the prefix
	    strncat(cname, dp->d_name, MAXLENGTH);  
	    enqueue(cname,&nameq);
	  }
	}
	closedir (dirp);
      } else { 
	// test if it is a regular file and not a device or link -- TO-DO
	struct stat file_info;
	//int fd = open(dname, O_RDONLY);
	lstat(dname, &file_info);
	if(S_ISREG(file_info.st_mode)){
	// if this is a regular file, then process it -- TO-DO
	printf(" processing file: %s\n", dname);
	numOfFiles++;
	avgFileSize = avgFileSize + file_info.st_size;
	if(numOfFiles == 1){
	sFileSize  = file_info.st_size;
	lFileSize  = file_info.st_size;
	leastRecent = file_info.st_mtime;
	mostRecent = file_info.st_mtime;
	strcpy(leastRecentFile, dname);
	strcpy(mostRecentFile, dname);
	
	}
	else{
	if(file_info.st_size <= sFileSize){
	  sFileSize = file_info.st_size;
}
	if(file_info.st_size >= lFileSize){
	  lFileSize = file_info.st_size;
}
	if(file_info.st_mtime < leastRecent){
	  leastRecent = file_info.st_mtime;
	  strcpy(leastRecentFile, dname);
	}
	if(file_info.st_mtime > mostRecent){
	  mostRecent = file_info.st_mtime;
	  strcpy(mostRecentFile, dname);
	}
	}

	}
      }      
    } // while
    printf("The smallest file size is: %d\n", sFileSize);
    printf("The largest file size is: %d\n", lFileSize);
    printf("The average file size is: %d\n", avgFileSize/numOfFiles);
    printf("Total number of directories: %d\n", numofDir);
    printf("Total number of %d regular files\n",numOfFiles);
    printf("Name of most recently modified file: %s\n", mostRecentFile);
    printf("Name of least recently modified file: %s\n", leastRecentFile);
}

// initialize queue data structure
void initq(que_t *q) {
  q->head = q->tail = NULL;
}

// test whether queue data structure is empty
bool queue_empty(que_t q) {
  if (NULL == q.head) {
     return true;
  } else {
    return false;
  }
}

// add an element to queue
void enqueue(char *name, que_t *q) {
  item_t *temp;
  
  temp = (item_t *)malloc(sizeof(item_t));
  strncpy(temp->name,name,MAXLENGTH);
  temp->next = NULL;
  
  if (true == queue_empty(*q)) {
    q->head = temp;
    q->tail = temp;
  } else {
    q->tail->next = temp;
    q->tail = q->tail->next;
  }
}

// remove an element from the front of the queue
void dequeue(que_t *q) {
  item_t *temp;
  
  if (true == queue_empty(*q)) {
    printf(" error in dequeue \n");
    exit(-1);
  } else {
    temp = q->head;
    q->head = q->head->next;
    free(temp);
  }
}

// find element at front of queue without removing
void peek_front(char *name, que_t q) {
  if (true == queue_empty(q)) {
    printf(" error in dequeue \n");
     exit(-1);
  } else {
    strncpy(name, q.head->name, MAXLENGTH);
  }
} 
