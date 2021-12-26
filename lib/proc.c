

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "proc.h"


const int proc_buffer_default_size = 8*1024;

int
run_proc_a(char** out,  char *const cmd[])
{
  int pid, ret;
  int pipes[2];
  char* buffer = (char*)malloc(proc_buffer_default_size);

  if(pipe2(pipes, O_CLOEXEC) != 0)
  {
    perror("Error creating pipes");
    return 1;
  }

  printf("about to fork?\n");
  if((pid = fork()) == -1)
  {
    perror("Error forking");
    return 1;
  }

  if(pid == 0)
  { //child
    if(dup2(pipes[1], STDOUT_FILENO)  == -1)
    {
      perror("Error duplicating stdout");
      exit(1);
    }
    //close(pipes[1]);
    //close(STDERR_FILENO);
    // Exec subprocess
    execvp(cmd[0], cmd);
  }
  //if(0 > fcntl(pipes[0], F_SETFL, O_NONBLOCK)) {
  //  printf("ERROR: fnctl");
  //  exit(1);
  //}

  printf("pipes worked?\n");
  
  printf("the read is gonna start\n");
  ssize_t read_length = read(pipes[0], buffer, proc_buffer_default_size);
  printf("the read worked, readlen=%zd  errno=%d egain=%d\n", read_length, errno, EAGAIN);
  printf("the read worked, readlen %zd\n", read_length);
  if (read_length == proc_buffer_default_size) {
    perror("Buffer not large enough");
    return 1;
  }

  int child_status;
  waitpid(pid, &child_status, 0);
  printf("waitpid came back, child_status: %d\n", child_status);
  if(child_status != 0) {
    return 2;
  }

  *out = buffer;
  return 0;
}


/*
 * Run subprocess 'image' with arguments 'args' and copy all output 'out'
 */
int
run_proc(char** out, const char* image, ... /*args*/) 
{

  /* 
   * Collect Args 
   */
  va_list ap;
  const char* current_arg = image; 

  size_t argc = 1, arg_cap = 1;
  const char** argv = malloc(arg_cap * sizeof(char*));
  argv[0] = image;

  va_start(ap, image);
  while (current_arg)
  {
    current_arg = va_arg(ap, const char*);
    if (current_arg)
    {
      if (argc >= arg_cap) {
        arg_cap *= 2;
        argv = realloc(argv, arg_cap * sizeof(char*));
      }
      argv[argc] =  current_arg;
      argc ++;
    }
  }
  argv[argc] = 0;

  return run_proc_a(out, (char *const *)argv);
}

