#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/*In your ~/csci315/Lab1 directory, create a C program called cmds.c - this program should ask for 4 command line arguments of data types as follows: char, int, float, string. Your program won’t need to do much: it should start executing, check if the number of parameters provided by the user is 4 – terminate with an error message otherwise, then assign each of the values read in from the command line to a variable of the appropriate type, and finally, print to the terminal each of the variables and terminate.
 */


int main ( int argc, char*argv[])
{
  char *charPointer;
  char charLine;
  int intLine;
  float floatLine;
  char *stringLine;
 //char n[60];
  if (argc != 5)
    printf("Error! Enter 4 command line arguments.\n");
  else
    {
      charPointer = argv[1];
      charLine = *charPointer;
      intLine = atoi(argv[2]);
      floatLine = atof(argv[3]);
      stringLine = argv[4];
      printf("The 4 variables are: %c %d %.2f %s\n", charLine, intLine, floatLine, stringLine);
      //return 0;
    }
  return 0;
}

