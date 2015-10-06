#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include "wrappers.h"
#include <netinet/in.h>
 #include <arpa/inet.h>


#define MYPORT 9895

void printsin(struct sockaddr_in *sin, char *pname, char* msg);

void printsin(struct sockaddr_in *sin, char *pname, char *msg) {
  printf("%s\n", pname);
  printf("%s ", msg);
  printf("IP =  %s, " ,inet_ntoa(sin->sin_addr));
  printf("port = %d " ,(int)sin->sin_port);
  
  /**-- port: sin->sin_port (host integer type) 
     -- IP: sin->sin_addr (IP in dotted-decimal notation) **/
  printf("\n");
}


int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  
	struct sockaddr_in  s_in, from;

	struct { 
		char head; 
		unsigned long  body; 
		char tail;
	}msg;

	/*Create socket descriptor*/
  socket_fd = Socket (AF_INET, SOCK_DGRAM, 0);

  /*set all bytes in s_in to null*/
  bzero((char *) &s_in, sizeof(s_in));

  /* set the socket family to the internet*/
  s_in.sin_family = (short)AF_INET;

  /*  INADDR_ANY- makes sure an IPv4 wildcard address is used
  //converts the unsigned integer hostlong  from  host byte order to network byte order*/
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);

  
  /*The htons() function converts the unsigned short integer hostshort from
  // host byte order to network byte order.We're connecting a host to network so, //we must convert to network byte order*/
  s_in.sin_port = htons((unsigned short) MYPORT);

  printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  fflush(stdout);

  /*Bind assigns specified address to socket_fd-so, it doesn't exist just in name only*/
  Bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));

  for(;;) {
		fsize = sizeof(from);
    cc = Recvfrom(socket_fd, &msg, sizeof(msg), 0, (struct sockaddr *) &from, &fsize);
    printsin( &from, "recv_udp: ", "Packet from:");

    /*You're receiving so, you convert what you receive from network to your machine's(host) order
    //network to host long*/
    printf("Got data ::%c%ld%c\n", msg.head, (long) ntohl(msg.body),
    msg.tail); 
    fflush(stdout);
  }
  
  return 0;
}

