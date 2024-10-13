#include <unistd.h>
#include "parser.h"
#include "cmd_runner.h"
#include "our_string.h"
#include <signal.h>
#include "add_features.h"



int main(int argc, char *argv[], char *envp[]) {


  /*-Werror is turned on */
  /* Since these are unsed in the rest of the code, we do this to supress the compiler error*/
  (void)argc; (void)argv;

  JOB job;
  signal_child_setup();   /*Setup proper backgorund processing*/
  
  while(1) {

    signal_int_setup(); /*For custom handling of ctrl c when taking input*/
    get_usr_input(&job.usr_input);
    signal(SIGINT,SIG_IGN);       /*Dont want to be interruped in the process of creating a job*/

    if(validate_and_parse_job(&job)){
     resolve_command_path(&job, envp);
      if(string_compare("exit", job.pipeline[0].argv[0], 0)) break;
      
      if(string_compare("cd", job.pipeline[0].argv[0], 0)){
        my_cd(&job);
        continue;
      }

      run_job(&job, NULL);
    }
   
  }

  return 0;
}




