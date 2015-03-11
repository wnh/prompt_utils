


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int
main(int argc, char **argv)
{
  int pid,ret;
  if(-1 == (pid = fork()))
  {
    perror("Error forking git");
    exit(1);
  }

  if(pid == 0)
  {
    /*
     * Use dup2(int, int) do duplicate stdout so you can look at it in the
     * parent process
     */
    ret =  execl("/usr/bin/git", "git", "status", "-s", (char*)0);
    return ret;
  }

  printf("the parent");
}
