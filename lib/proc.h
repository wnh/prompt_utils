
#ifndef __PROC_H__
#define __PROC_H__

#ifndef RUN_PROC_BUFSIZE
#define RUN_PROC_BUFSIZE 5120  /* 5k */
#endif

int run_proc_a(char** out,  char *const cmd[]);
int run_proc(char** out, const char* image, ... /*args*/);

#endif
