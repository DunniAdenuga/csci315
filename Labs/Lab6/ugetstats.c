#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*------------------------------------------------------------------------
 * Program:   getstats 
 *
 * Purpose:   allocate a socket, connect to a server, 
 *            request file transfer statistics
 *
 * Syntax:    getstats [ host ] [ port ]
 *
 *		 host  - name of a computer on which server is executing
 *		 port  - protocol port number server is using
 *
 *------------------------------------------------------------------------
 */

#define BUFSIZE 1000
#define NAMELEN 257

int main(int argc, char* argv[]) {

  
  struct sockaddr_in dest;
  struct sockaddr_in in;
  struct hostent *hostptr;
 struct {
  int num;
  char buf[60000];
}outmsg;

struct message {
    int num;
    char requestType[6];

  } msgbuf;

 int	sd, sd2;		           // socket descriptor			
  int	port;		         // protocol port number		
  char	*host;		     // pointer to host name		
  int	n;		           // number of characters read		
  char	buf[BUFSIZE];  // buffer for data from the server	
  int   bytes_read;    // number of bytes read from socket
  int   bytes_expected;

  memset((char *)&dest,0,sizeof(dest)); // clear sockaddr structure	
  dest.sin_family = (short)AF_INET;	      // set family to Internet	
  
  // Check command-line arguments
  
  if (argc < 3) {
    printf("usage: getstats [ host ] [ port ]\n");
    exit(-1);
  }

  hostptr = gethostbyname(argv[1]);		
  port = atoi(argv[2]);	

  //copy bytes for host to destination socket
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);

  if (port <= 0) {	
    // test for legal value		
    // print error message and exit	
    fprintf(stderr,"GETSTATS: bad port number %s\n",argv[2]);
    exit(1);
  }
else{
    dest.sin_port = htons((u_short) port);
  }
  
  // Create a socket. 
  
  sd = Socket(AF_INET, SOCK_DGRAM, 0);
  if (sd < 0) {
    fprintf(stderr, "GETSTATS: socket creation failed\n");
    exit(1);
  }
  
  
  
  // Repeatedly read data from socket and write to user's screen. 
  
  strcpy(msgbuf.requestType, "stats");
 

   Sendto(sd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&dest, sizeof(dest));
   int fsize;
   int stuff = 0;
   fsize = sizeof(in);
   Recvfrom(sd, &outmsg, sizeof(outmsg), 0, (struct sockaddr *) &in, &fsize);
   if(stuff < outmsg.num){
	    printf("%s\n", outmsg.buf);
	    stuff++;
   }
   else{
     printf("Error in arrival of data\n");
   }
  Close(sd);
  
  // Terminate the client program gracefully. 
  
  exit(0);
}
