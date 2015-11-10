#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
struct account {
 int id;
 char name[80];
 double balance;
};

 struct account myaccount;
 struct account myaccount2;
 strcpy(myaccount.name, "Dunni");
 myaccount.id = 2;
 myaccount.balance = 523.5;

 //FILE * file = fopen("newFile", "w");
 //fwrite(myaccount, sizeof(account), file);
 int fd = open("myaccount.txt", O_CREAT|O_RDWR, S_IRWXU);
 int m = write(fd, &myaccount, sizeof(myaccount));
 //close(fd);

 int l = read(fd, &myaccount2, sizeof(struct account));
 printf("%f l - %d fd - %d m - %d\n", myaccount2.balance, l, fd, m);
 close(fd);
}
