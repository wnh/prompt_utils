/*
 * Small utility to print a compressed version of your current working
 * directory
 */


#include  <stdio.h>
#include  <unistd.h>
#include  <stdlib.h>

#define PATH_MAX 1024

int
main(int argc, char **argv)
{

  int c, hmflg = 0, width = -1;
  char path[PATH_MAX];
  char *home;

  while((c = getopt(argc, argv, "hw:")) != -1)
  {
    switch(c)
    {
    case 'w':
      width = atoi(optarg);
      break;

    case 'h':
      hmflg++;
      break;
    }
  } 
  
  if (getcwd(path, PATH_MAX * sizeof(char)) == NULL )
  {
    perror("Error getting current working directory");
    return 1;
  }

  char *npath = path;
  npath += 2;
  fputs(npath, stdout);
  printf("\n");

  if (hmflg)
  {
    home = getenv("HOME");
    printf("home=%s\n", home);
  }

  printf("expand-home=%d\n", hmflg);
  printf("width=%d\n", width);

  return 0;
}
