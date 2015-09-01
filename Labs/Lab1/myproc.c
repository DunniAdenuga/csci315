# include <unistd.h>
/*
In your ~/csci315/Lab1 directory, create a program called myproc.c that spawns two child processes. The parent should run an infinite loop printing to the terminal the string “parent:” followed by an increasing counter value, and a new line character. The children should also run an infinite loop printing to the terminal the string “child1:” or “child2:“ followed by an increasing counter value, and a new line character. The parent and the children should have separate counter variables! At the end of each iteration of their respective loops, each process’ counter variable gets incremented by one. The output of the program should resemble what appears in the box below. Note that the specific values of the counters will be different in your program and that the output will scroll by fast.
*/

//both child processes would have pid of 0 ? How do I differentiate them ?
int main()
{
  pid_t pid;//process id
  int i = 1;//variable counter for parent
  int x = 1; //variable counter for child 1
  int y = 1; //variable counter for child 2
  pid = fork();//make child 1
 
      if(pid == 0)
	{
	  while(1)
	    {
	  printf("child1: %d\n",x);
	  x++;
	    }
	}
       else
	{
	  pid = fork();//make child 2
	  if(pid ==0)
	    {
	       while(1)
		 {
	  printf("child2: %d\n",y);
	  y++;
		 }
	    }
	  else
	    {
	  while(1)
	    {
	  printf("parent: %d\n", i);
	  i++;
   
	    }
	    }
	}
}
