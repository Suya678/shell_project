
#include <unistd.h>
#include <fcntl.h>
#include "parser.h"
#include "cmd_runner.h"
#include "our_string.h"
#include <stdio.h>


int main(char argc, char *argv[], char *envp[]) {
  JOB job;
  unsigned int num = 0;
  get_usr_input(&job.usr_input);

  if(validate_and_parse_job(&job) == TRUE ) {
    run_job(&job);
  }

  return 0;
}
