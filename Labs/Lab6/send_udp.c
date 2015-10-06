/*
 * Copyright (c) 2015 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "wrappers.h"

#define MYPORT 9895

int main(int argc, char *argv[])
{
  int socket_fd;

  // address of destination socket
  struct sockaddr_in  dest;

  // pointer to host data structure
  struct hostent *hostptr;
  
  // data structure for a message
  struct message { 
    char head; 
    u_long body; 
    char tail; 
  } msgbuf;
  
  // //Create socket descriptor
  socket_fd = Socket (AF_INET, SOCK_DGRAM, 0);

  // set a sectiion of memory to null
  memset((void*) &dest, 0, sizeof(dest));

  //return info about host from name of host
  hostptr = gethostbyname(argv[1]);

  // set the socket family to the internet
  dest.sin_family = (short) AF_INET;

  //copy bytes for host to destination socket
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);

  // convert from host byte to network byte order
  dest.sin_port = htons((u_short) MYPORT);

  // build message to send
  msgbuf.head = '<';

	// because we're sending from host to the network.
	msgbuf.body = htonl(getpid());
  msgbuf.tail = '>';

  // transmit message to another socket
  Sendto(socket_fd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&dest, sizeof(dest));

  return 0;
}
