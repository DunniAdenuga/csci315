#include "wrappers.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>

pid_t Fork(void)
{
  pid_t pidy = fork();
  if(-1 == pidy)
{
  perror("Error! No child process was created.");
  //printf("errno = %d.\n", errno);
  exit(-1);
}
  return pidy;
}


int Pipe(int pipefd[2])
{
  if(pipe(pipefd) == -1)
    {
      perror("Pipe Failed");
      exit(-1);
    }
  return 1;
}

int Write(int fd, const void *buf, size_t count)
{
  int wid = write(fd, buf, count);
  if( wid  == -1)
    {
      perror("Write Failed");
      exit(-1);
    }
  return wid;
}

 int Read(int fd, void *buf, size_t count)
{
  int rid = read(fd, buf, count);
  if(rid  == -1)
    {
      perror("Read Failed");
      exit(-1);
    }
  return rid;
  }

pid_t Wait(int *status){
  pid_t x;
x = wait(status);
 if(x == -1){
 perror("Wait Failed");
      exit(-1);
    }
  return x;
}

pid_t Waitpid(pid_t pid, int *status, int options){

  pid_t wid;
  wid = waitpid(pid, status, options); 
if(wid == -1){
 perror("Wait-Pid Failed");
      exit(-1);
    }
  return wid;
}

int Open(const char *pathname, int flags){
  int oid;
  oid = open(pathname, flags);
  if(oid == -1){
    perror("Open Failed");
      exit(-1);
    }
  return oid;
}

int Close(int fd){
  int cid;
  cid = close(fd);
  if(cid == -1){
    perror("Close Failed");
      exit(-1);
    }
  return cid;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
  int cid;
  cid = connect(sockfd, addr, addrlen);
  if(cid == -1){
    perror("Connect Failed");
      exit(-1);
    }
  return cid;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
  int bid;
  bid = bind(sockfd, addr, addrlen);
  if(bid == -1){
    perror("Bind Failed");
      exit(-1);
    }
  return bid;
}

int Listen(int sockfd, int backlog){
  int lid;
  lid = listen(sockfd, backlog);
  if(lid == -1){
    perror("Listen Failed");
    exit(-1);
  }
  return lid;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
  int aid;
  aid = accept(sockfd,addr, addrlen);
  if(aid < 0){
    perror("Accept Failed");
    exit(-1);
  }
  return aid;
}

int Socket(int domain, int type, int protocol){
  int sd;
  sd = socket(domain, type, protocol);
  if(sd == -1){
    perror("Socket Failed");
    exit(-1);
  }
  return sd;
}
