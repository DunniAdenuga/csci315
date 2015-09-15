/**
Write a program called mytime.c, which calls gettimeofday(2), passes the results to ctime(3), and then prints to the screen the resulting string. Whether you have used these functions before or not, take the time to read their man pages to understand what they do and how to use them.
 **/

#include <sys/time.h>
#include<time.h>

int main()
{
  struct timeval tv;
  char ans[500];
  //struct timeval test = *tv;
  gettimeofday(&tv, NULL);
  
  printf("The current time is: %s", ctime(&tv.tv_sec));

}
