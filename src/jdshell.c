
#include <unistd.h>
#include "parser.h"
#include "cmd_runner.h"
#include "our_string.h"
#include <signal.h>
#include "add_features.h"


#define EXIT_CODE 10


void run_shell(char *envp[]);

int main(char argc, char *argv[], char *envp[]) {
int status;
pid_t pid_child;
bool exit_command = FALSE;
signal(SIGINT,SIG_IGN);

while (1){
  
  pid_child = fork();
  
  if(pid_child == 0){
    signal(SIGINT,SIG_DFL);
    run_shell(envp);
  } else if(pid_child == -1){
    perror(NULL);
    return;
  }
  waitpid(pid_child,&status, 0);
  if(WEXITSTATUS(status) == EXIT_CODE) break;
  print_string("\n");
}

  return 0;
}



void run_shell(char *envp[]){

  JOB job;
  signal_child_setup();/*Setup proper backgorund processing*/
  bool is_job_valid;  
  
  while(1) {
    get_usr_input(&job.usr_input);
    if(validate_and_parse_job(&job)){
     resolve_command_path(&job, envp);
      if(string_compare("exit", job.pipeline[0].argv[0], 0)) _exit(EXIT_CODE);
      run_job(&job, NULL);
    }
  }



}
