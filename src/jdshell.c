
#include <unistd.h>
#include "parser.h"
#include "cmd_runner.h"
#include "our_string.h"
#include <signal.h>
#include "add_features.h"


#define EXIT_CODE 10
#define CHANGE_DIR_CODE 20

void run_shell_session(char *envp[], int change_directory_fd);
void create_pipe_with_cloexec(int pipe_fd[2]);
bool check_if_internal_commands(JOB *job, int change_directory_fd) ;






int main(int argc, char *argv[], char *envp[]) {


  JOB job;
  signal_child_setup();/*Setup proper backgorund processing*/
  signal_int_setup();
  while(1) {
    get_usr_input(&job.usr_input);
    if(validate_and_parse_job(&job)){
     resolve_command_path(&job, envp);
      if(string_compare("exit", job.pipeline[0].argv[0], 0)) break;
      run_job(&job, NULL);
    }
   
  }


  return 0;
}




