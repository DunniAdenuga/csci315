#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readwrite.h"
#include "wrappers.h"

/*------------------------------------------------------------------------
 * Program:   getfile 
 *
 * Purpose:   allocate a socket, connect to a server, transfer requested
 *            file to local host, and print file contents to stdout
 *
 * Syntax:    getfile [ host ] [ port ] [ file ] 
 *
 *		 host  - name of a computer on which server is executing
 *		 port  - protocol port number server is using
 *               file  - complete path of file to retrieve
 *
 *------------------------------------------------------------------------
 */

#define BUFSIZE 1000
#define NAMELEN 257

int main(int argc, char* argv[]) {
  struct sockaddr_in in;
struct {
  int num;
  char buf[60000];
}outmsg;

  //struct	sockaddr_in sad; // structure to hold an IP address
  struct sockaddr_in dest;
  //struct addrinfo hint;
  //struct addrinfo *serverptr;
  struct hostent *hostptr;

  struct message {
    int num;
    char requestType[6];
    char fileName[257];
  } msgbuf;

  int	sd, sd2;		                 // socket descriptor	       	
  int	port;		               // protocol port number		
  char	*host;		           // pointer to host name		
  char	buf[BUFSIZE];	       // buffer for data from the server	
  char  file_name[NAMELEN];  // buffer for full path to file
  int   bytes_read;          // number of bytes read from socket
  int   bytes_expected;

  memset((void *)&dest,0,sizeof(dest)); // clear sockaddr structure	
  dest.sin_family = (short)AF_INET;	          // set family to Internet	
  
  // Check command-line arguments
  
  if (argc < 4) {
    printf("usage: getfile [ host ] [ port ] [ file ]\n");
    exit(-1);
  }

  hostptr = gethostbyname(argv[1]);		
  port = atoi(argv[2]);	
  strncpy(msgbuf.fileName, argv[3], 257);

  //copy bytes for host to destination socket
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);

  if (port <= 0) {	
    // test for legal value		
    // print error message and exit	
    fprintf(stderr,"GETFILE: bad port number %s\n",argv[2]);
    exit(1);
  }
  else{
    dest.sin_port = htons((u_short) port);
  }
  
  // Create a socket. 
  
  sd = Socket(AF_INET, SOCK_DGRAM, 0);
  if (sd < 0) {
    fprintf(stderr, "GETFILE: socket creation failed\n");
    exit(1);
  }
  
 
  strcpy(msgbuf.requestType, "get");
  
  msgbuf.num = 1;
 Sendto(sd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&dest, sizeof(dest));
  int fsize;
  int stuff = 0;
   fsize = sizeof(in);
 Recvfrom(sd, &outmsg, sizeof(outmsg), 0, (struct sockaddr *)&in, &fsize);
 if(stuff < outmsg.num){
  printf("%s", outmsg.buf);
  stuff++;
 }
else{
     printf("Error in arrival of data\n");
   }
  Close(sd);
  
  // Terminate the client program gracefully 
  
  exit(0);
}
