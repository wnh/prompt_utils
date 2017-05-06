
#include <stdio.h>
#include <string.h>
#include "lib/proc.h"

int
main(int argc, char **argv)
{
  char* gitbuff;
  int out = run_proc(&gitbuff, "git", "branch", "--list", 0);
  if (out != 0)
  {
    exit(1);
  }

  char *token;
  char *sep=" \r\n";
  int next = 0;
  while((token = strsep(&gitbuff, sep)) != NULL)
  {
    if (token[0] == '*')  {
      token = strsep(&gitbuff, sep);
      printf("(%s)", token);
      break;
    }
   }
  return 0;
}
