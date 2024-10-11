
#include <unistd.h>
#include "parser.h"
#include "cmd_runner.h"
#include "our_string.h"

#include <signal.h>

#include "add_features.h"


int main(char argc, char *argv[], char *envp[]) {

  JOB job;
  signal_child_setup();/*Setup proper backgorund processing*/

  bool is_job_valid;
  get_usr_input(&job.usr_input);  
  while(1) {
    is_job_valid = validate_and_parse_job(&job);
    if(is_job_valid){
     resolve_command_path(&job, envp);
      if(string_compare("exit", job.pipeline[0].argv[0], 0)) break;
      run_job(&job, NULL);
    }
    get_usr_input(&job.usr_input);
  }

  return 0;
}
