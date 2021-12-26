
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lib/proc.h"
#include "lib/scanner.h"

#define BUF_LEN 8192

int
main(int argc, char **argv)
{

  char gitbuff[BUF_LEN];
  FILE *gitfile = popen("git branch --list 2>/dev/null", "r");
  size_t read = fread(&gitbuff, 1, BUF_LEN-1, gitfile);
  pclose(gitfile);

  //char *token;
  char *sep="\r\n";
  int next = 0;
  Scanner line, token;
  ScanInit(&line, gitbuff, sep);
  while(ScanHasNext(&line))
  {
    char *ln = ScanNext(&line);
    size_t len = strlen(ln);
    if (len > 0 && ln[0] == '*')  {
      ScanInit(&token, ln, " ");
      ScanHasNext(&token);
      ScanHasNext(&token);
      printf("(%s)", ScanNext(&token));
      break;
    } 
  }
  return 0;
}
