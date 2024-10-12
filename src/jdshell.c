
#include <unistd.h>
#include "parser.h"
#include "cmd_runner.h"
#include "our_string.h"
#include <signal.h>
#include "add_features.h"


#define EXIT_CODE 10


void run_shell_session(char *envp[]);

int main(int argc, char *argv[], char *envp[]) {
int status;
pid_t pid_child;
bool exit_command = FALSE;
signal(SIGINT,SIG_IGN);

while (1){
  
  pid_child = fork();
  
  if(pid_child == 0){
    signal(SIGINT,SIG_DFL);
    run_shell_session(envp);
  } else if(pid_child == -1){
    perror(NULL);
    return 0;
  }
  waitpid(pid_child,&status, 0);
  if(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_CODE) break;/* Checks if shell terminated normally and exit was entered*/
  print_string("\n");
}
  return 0;
}


/**
 * @brief Implements the main shell loop for processing user commands
 *
 * This function initializes the shell environment, sets up signal handling,
 * and enters a continuous loop to read and execute user input commands.
 * It handles background processing, command parsing, and execution.
 * The shell exits when the user inputs the "exit" command.
 *
 * @param envp[] An array of environment variables inherited from the parent process.
 */
void run_shell_session(char *envp[]){

  JOB job;
  signal_child_setup();/*Setup proper backgorund processing*/

  while(1) {
    get_usr_input(&job.usr_input);
    if(validate_and_parse_job(&job)){
     resolve_command_path(&job, envp);
      if(string_compare("exit", job.pipeline[0].argv[0], 0)) _exit(EXIT_CODE);
      run_job(&job, NULL);
    }
  }

}
