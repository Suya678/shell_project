
#include <unistd.h>
#include <fcntl.h>
#include "parser.h"
#include "cmd_runner.h"
#include "our_string.h"
#include <stdio.h>
#include <signal.h>
/*
The sigaction structure is defined as something like:

           struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };
*/

int main(char argc, char *argv[], char *envp[]) {
  
  struct sigaction sa;
  sa.sa_handler = signal_child_handler; //in cmd_runner.c
  sigemptyset(&sa.sa_mask);        // Initialize an empty set *i got this from chatgpt it says we need it for predictability*

  if (sigaction(SIGCHLD, &sa, NULL) == -1) { //SIGCHLD is child stopped or terminated
    perror("sigaction");
    return 1;
}

  JOB job;
  
  get_usr_input(&job.usr_input);
  
  if(validate_and_parse_job(&job) == TRUE ) {
    run_job(&job, NULL);
    sa.sa_flags = 0;
  }

  return 0;
}
