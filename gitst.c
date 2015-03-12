


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define GITBUF 2048

int
main(int argc, char **argv)
{

  int pid, ret;
  int pipes[2];

  if(pipe(pipes) != 0)
  {
    perror("Error creating pipes");
    exit(1);
  }

  if(-1 == (pid = fork()))
  {
    perror("Error forking git");
    exit(1);
  }

  if(pid == 0) //child
  {
    /*
     * use pipe(int[2]) to make a pipe to duplicate
     * Use dup2(int, int) do duplicate stdout so you can look at it in the
     * parent process
     */
    if(dup2(pipes[1], STDOUT_FILENO)  == -1)
    {
      perror("Error duplicating stdout");
      exit(1);
    }
    ret =  execl("/usr/bin/git", "git", "status", "-s", "-b", (char*)0);
  }

  wait(pid);
  printf("subprocess finished\n");

  char gitbuff[GITBUF];
  size_t gitlen;
  char b;

  gitlen = read(pipes[0], gitbuff, GITBUF);

  // TODO(wnh): Make this not write into someone elses memory
  gitbuff[gitlen] = '\0';

  printf("Read %d chars from git\n", (int)gitlen);
  printf("stdout = %s", gitbuff);
}

