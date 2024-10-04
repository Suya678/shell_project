#include "cmd_runner.h"
/**
 * @brief The funcition checks if the user wants the command to be ran in background
 *
 * This function will check if the last valid token enetered by thr user was an "&".
 * If so, it sets the process_in_background flag to TRUE otherwise it will remain
 * FALSE.
 * @param Command *command structure containing the command attributes including the
 *                the flag to indcate background_processing
 *
 * @return Does not return anything direcly but modifies the process_in_background
 *         flag in the command structure
 
void check_for_background_processing(JOB *job){
  unsigned int num_tokens = job->argc;
  command->process_in_background = FALSE; /*Needs to reset every time
  

  if(string_compare(command->argv[num_tokens - 1],"&",0) == TRUE) {
      command->argv[num_tokens-1] = NULL;
      command->process_in_background = TRUE;
    }
    
  
}
*/



/**
 * @brief The funcition will run a command from the command strucuture
 *
 * This function will first fork a child process. The child process will then run the
 * commadn in the commadn structure.Depending on the background_processing flag, the 
 * parent process will decide if it needs to wait for the child to exit before continuing.
 *
 * @param Command *command structure containing the command attributes 
 *
 * @return Does not return anything
 */
void run_command(Command *command) {
  pid_t pid;
  int status;

  pid = fork();
  
  if(pid == 0)
  {
    execve(command->argv[0], command->argv, NULL);
    write(FD_STD_OUT,"ERROR: COMMAND NOT FOUND OR COULD NOT BE EXECUTED \n", 52);
    _exit(1);
    
  } else if(pid == -1){
    write(FD_STD_OUT, "Fork failed in run_command\n", 23);
    return;
  }

    waitpid(pid, &status, 0);

}
