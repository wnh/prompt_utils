/*
 * Small utility to print a compressed version of your current working
 * directory
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX 1024

void useage(void);

int
main(int argc, char **argv)
{

  int c, width = -1;
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
      useage();
      exit(0);
      break;
    }
  } 
  
  if (getcwd(path, PATH_MAX * sizeof(char)) == NULL )
  {
    perror("Error getting current working directory");
    return 1;
  }

  home = getenv("HOME");
  printf("home=%s\n", home);
  printf("width=%d\n", width);


  int homelen = strlen(home);

  char homematch = 1; 
  for(int i=0; i < homelen; i++ )
  {
    if (path[i] != home[i]) 
    {
      homematch = 0;
      break;
    }
  }

  printf("Home match? %d\n", homematch);

  char *rest;
  if(homematch) {
    rest = (char*)path + (homelen);
    printf("the rest: %s\n", rest);
  }

  return 0;
}


void
useage()
{
  printf("Useage:  swd [OPTIONS]\n");
  printf("print a path to the current workng directory collapsed for space\n");
  printf("\n");
  printf("Options\n");
  printf("  -w <width>    confine the output to a maximum number of characters\n");
  printf("  -h            print this help message\n");
  printf("\n");
}
