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
int  starts_with(char*, char*, int);

int
main(int argc, char **argv)
{

  int c, width = -1;
  char pathbuf[PATH_MAX];
  char *home;
  char *path;
  int next = 0;
  char *lastpth = NULL;

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
  
  if (getcwd(pathbuf, PATH_MAX * sizeof(char)) == NULL )
  {
    perror("Error getting current working directory");
    return 1;
  }

  home = getenv("HOME");


  int homelen = strlen(home);
  int in_home = starts_with(home, pathbuf, homelen);


  if(in_home)
    path = pathbuf + homelen;
  else
    path = pathbuf;

  if (in_home) 
  {
    putchar('~');
  }

  while(*path != '\0')
  {
    if(next)
    {
      putchar(*path);
      next = 0;
    }

    if(*path == '/')
    {
      putchar(*path);
      next = 1;
      lastpth = path +2;
    }
    path++;
  }

  if(lastpth != NULL)
    puts(lastpth);
  else
    putchar('\n');

  return 0;
}

int
starts_with(char *needle, char *haystack, int len)
{
  int i;
  for(i=0; i < len; i++)
  {
    if(needle[i] != haystack[i])
    {
      return 0;
    }
  }
  return 1;
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
