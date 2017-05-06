
#ifndef LIB_PROC_H
#define LIB_PROC_H

#ifndef RUN_PROC_BUFSIZE
#define RUN_PROC_BUFSIZE 5120  /* 5k */
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int
run_proc_a(char** out,  char *const cmd[])
{
  int pid, ret;
  int pipes[2];
  char* buffer = (char*)malloc(RUN_PROC_BUFSIZE);

  if(pipe(pipes) != 0)
  {
    perror("Error creating pipes");
    return 1;
  }

  if((pid = fork()) == -1)
  {
    perror("Error forking");
    return 1;
  }

  if(pid == 0) //child
  {
    if(dup2(pipes[1], STDOUT_FILENO)  == -1)
    {
      perror("Error duplicating stdout");
      exit(1);
    }
    close(STDERR_FILENO);
    // Exec subprocess
    execvp(cmd[0], cmd);
  }

  int child_status;
  waitpid(pid, &child_status, 0);
  if(child_status != 0) {
    return 2;
  }

  size_t read_length = read(pipes[0], buffer, RUN_PROC_BUFSIZE);
  if (read_length == RUN_PROC_BUFSIZE)
  {
    perror("Buffer not large enough");
    return 1;
  }

  *out = buffer;
  return 0;
}


#endif /* LIB_PROC_H */


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

