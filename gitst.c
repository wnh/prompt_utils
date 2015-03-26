
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define GITBUF 2048

int
main(int argc, char **argv)
{
  int pid, ret;
  int pipes[2];
  char gitbuff[GITBUF];
  size_t gitlen;
  char b;
  char *br;
  int childst;

  if(pipe(pipes) != 0)
  {
    perror("Error creating pipes");
    exit(1);
  }

  if((pid = fork()) == -1)
  {
    perror("Error forking git");
    exit(1);
  }

  if(pid == 0) //child
  {
    if(dup2(pipes[1], STDOUT_FILENO)  == -1)
    {
      perror("Error duplicating stdout");
      exit(1);
    }
    close(STDERR_FILENO);
    ret =  execlp("git", "git", "status", "-z", "-b", (char*)0);
  }

  waitpid(pid, &childst, 0);
  if(childst != 0) {
    exit(2);
  }

  gitlen = read(pipes[0], gitbuff, GITBUF);
  br = &gitbuff[3];
  putchar('(');

  while(*br != '\0')
  {
    // Three dots separate the branch from the tracking branch
    if(*br == '.' && *(br+1) == '.' && *(br+2) == '.') break;
    putchar(*br++);
  }

  putchar(')');
  putchar('\n');
}

