#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
In your ~/csci315/Lab1 directory, create a C program called cmdreverse.c - this program should ask for 1 command line arguments of string. Your program should check if the number of parameters provided by the user is exactly 1 and terminate with an error message otherwise. If all is well, your program should reverse the entire string passed in as command line argument and print it out to the terminal. Note that your program must work with strings that contain any type of blank spaces.

 */

int main(int argc, char*argv[])
{
  char ans[20];
  int k = 0; 
  int i;//loop variable
  if (argc != 2)
    printf("Error! Only 1 command line argument required.\n");
  else
    {
      for(i = strlen(argv[1]); i > 0; i--)
	{
	  ans[k] = argv[1][i-1];
	  k++;
	}
  printf("%s\n", ans);
    }

}
