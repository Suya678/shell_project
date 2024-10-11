
#include <unistd.h>
#include <fcntl.h>
#include "parser.h"
#include "cmd_runner.h"
#include "our_string.h"
#include <stdio.h>
#include <signal.h>

int main(char argc, char *argv[], char *envp[]) {
  signal_child_setup();
  
  JOB job;
  
  get_usr_input(&job.usr_input);
  
  if(validate_and_parse_job(&job) == TRUE ) {
    run_job(&job, NULL);
    sa.sa_flags = 0;
  }

  return 0;
}
