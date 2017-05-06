
#include <stdio.h>
#include "lib/proc.h"

int
main(int argc, char **argv)
{

  char* gitbuff;
  int out = run_proc(&gitbuff, "git", "branch", "--list", 0);
  //int out = run_proc(&gitbuff, "ls", "-l", "-h", 0);
  if (out != 0)
  {
    fprintf(stderr, "Error running subprocess:%d\n", out);
    exit(1);
  }
  //printf("run_proc exit code = %d\nresponse= '''%s'''\n", out, gitbuff);

  char *br;

  br = gitbuff;
  putchar('(');

  while(*br++ != '*') {}
  // skip the '*' and the space after it
  br++;
  while(*br != '\n')
  {
    putchar(*br++);
  }

  putchar(')');
  putchar('\n');
}

