#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "readwrite.h" 
#include "wrappers.h"
#include <pthread.h>

#define MAX_FILE_PATH   257 // length of path+filename and null char  
#define BUFFER_SIZE     512 // size of file read buffer    
#define	QLEN		6   // size of request queue
int	visits	    =   0;  // counts client connections
int fileR = 0;
int statR = 0;
int fileErr = 0;
int avg = 0;
pthread_t pid[10];
pthread_mutex_t lock1;
pthread_mutex_t lock2;
pthread_mutex_t lock3;
pthread_mutex_t lock4;
/*------------------------------------------------------------------------
 * Program:   fileserver
 *
 * Purpose:   allocate a socket and then repeatedly execute the following:
 *		(1) wait for the next connection from a client
 *		(2) send a short message to the client
 *		(3) close the connection
 *		(4) go back to step (1)
 *
 * Syntax:    fileserver [ port ]
 *
 *		 port  - protocol port number to use
 *
 *------------------------------------------------------------------------
 */
     struct message { 
		int num; 
		char  requestType[6]; 
		char fileName[257];
       int portNum;
       char* host;
       struct sockaddr_in out;
	};


void*process_request(void*stuff);

void *process_request(void *stuff)
{
  struct {
  int num;
  char buf[60000];
}outmsg;
struct sockaddr_in from;
 
  
	
	int file_req;
	int bytes_read;     
	int bytes_expected;
	struct message *msgS;
	msgS = (struct message*) stuff;
	struct sockaddr_in outer = msgS->out;
	int sd = msgS->num ;
	if (strncmp(msgS->requestType, "get", 4) == 0) {
		// Request is "get file", so now read full path to file
		// Pre-condition: full path string is no more than 256 chars long               
	  pthread_mutex_lock(&lock1);
	        fileR++;
	   pthread_mutex_unlock(&lock1);
	
		printf("SERVER: file requested is %s\n", msgS->fileName);
		fflush(stdout);

		if ((file_req = Open(msgS->fileName,O_RDONLY)) == -1) {
			printf("SERVER: file not found\n");
			fflush(stdout);
			pthread_mutex_lock(&lock2);
			fileErr++;
			pthread_mutex_unlock(&lock2);
			
		} 
		else {
			printf("SERVER: file %s found\n", msgS->fileName);
			fflush(stdout);
		pthread_mutex_lock(&lock4);
		struct stat sbuf;
		fstat(file_req, &sbuf);
		int size = sbuf.st_size;
		avg = (avg + size)/fileR;
		pthread_mutex_unlock(&lock4);
		bytes_read = Readn(file_req,outmsg.buf, BUFFER_SIZE);
	
			do {
			  outmsg.num++;
				Sendto(sd, &outmsg, sizeof(outmsg),0,(struct sockaddr*)&outer, sizeof(outer));
				bytes_read = bytes_read - 65,535;				
			} while (bytes_read > 0);

		}
	}
	else if (strncmp(msgS->requestType, "stats", 6) == 0) {
		// Request is "get stats"
		printf("SERVER: stats requested\n");
		pthread_mutex_lock(&lock3);
		statR++;
		pthread_mutex_unlock(&lock3);
		
	
		sprintf(outmsg.buf, "Number of file requests: %d time(s).\nNumber of status requests: %d time(s).\nNumber of file errors: %d time(s).\nAverage length of file requests: %d.\nServer has been contacted %d time(s).\n ", fileR,statR,fileErr, avg, visits);
		outmsg.num++; 
	Sendto(sd, &outmsg, sizeof(outmsg),0,(struct sockaddr*)&outer, sizeof(outer));
	
	}
	else {
		// Request is invalid
		printf("SERVER: invalid request\n");
	}
	return (NULL);
}

int main(int argc, char* argv[]) {
	struct sockaddr_in s_in;  // structure to hold server's address	
	struct sockaddr_in from;  // structure to hold client's address	
	int sd, sd2;	           // socket descriptors			
	int port;		             // protocol port number		
	socklen_t alen;          // length of address			
	//pthread pid;                 // process id
	int fsize;
	struct message msg;

	 /*set all bytes in s_in to null*/
	bzero((char *) &s_in, sizeof(s_in));

	/* set the socket family to the internet*/
  s_in.sin_family = (short)AF_INET;

  /*  INADDR_ANY- makes sure an IPv4 wildcard address is used
  //converts the unsigned integer hostlong  from  host byte order to network byte order*/
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);


	// Check command-line argument for protocol port
	if (argc > 1) {			
		port = atoi(argv[1]);	        
	}
	else {
		printf("Usage: fileserver [ port ]\n");
		exit(-1);
	}

	if (port > 0)	
		// test for illegal value	
		 s_in.sin_port = htons((unsigned short) port);
	else {				
		// print error message and exit	
		fprintf(stderr,"SERVER: bad port number %s\n",argv[1]);
		exit(1);
	}

	// Create a socket 
	sd = Socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		fprintf(stderr, "SERVER: socket creation failed\n");
		exit(1);
	}

	// Bind a local address to the socket 
	Bind(sd, (struct sockaddr *)&s_in, sizeof(s_in));  
	while(1){
	
	
	fsize =sizeof(from);
	ssize_t cc;
	cc =Recvfrom(sd, &msg, sizeof(msg), 0, (struct sockaddr *) &from, &fsize);
	visits++;
	msg.num = sd;
	msg.portNum = port;
	msg.out = from;
		if(visits < 10){
		  pthread_create(&pid[visits-1], NULL, process_request, (void*)&msg);
		  }
	}
	
		//Close(sd); // parent close connection
	

		
	
	usleep(2000);
	//Close(sd2); // parent closes connected socket
	//return(0); // will never get here, but to shut up the compiler
}


