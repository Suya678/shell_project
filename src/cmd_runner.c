#include "cmd_runner.h"

#define READ_MODE 0
#define WRITE_MODE 1
#define PIPE_READ_END 0
#define PIPE_WRITE_END 1
#define NO_FD_TO_CLOSE -1

static void handle_multi_pipeline_job(JOB *job, char *envp[]);
static void handle_single_pipeline_job(JOB *job, char *envp[]);
static bool initialize_file_descriptors(JOB *job, int *input_fd, int *output_fd);
static void _close(int fd);
static void redirect_fd(int old_fd, int new_fd);
static void redirect_fd(int old_fd, int new_fd);
static void run_command(Command *command, int input_fd, int output_fd, int fd_close, char *envp[]);


/**
 * @brief Handles running of a single job 
 * 
 * This function runs a job using helper functions. It also decides to
 * wait for child processes to finished based on whether the background
 * property in the job struc is false or true. 
 * 
 * @param job pointer to the JOB structure containing the pipeline stages.
 * 
 * @return Does not return anything.
 */
void run_job(JOB *job, char *envp[]) {
  int status;
  pid_t pid = fork();

  if(pid == 0) {  
    signal(SIGINT, SIG_DFL); // Reset the sig ignore signal so children can still be kileld
    
    if(job->num_stages > 1){
      handle_multi_pipeline_job(job, envp);
    } else {
      handle_single_pipeline_job(job,envp);
    }
    while (wait(&status)> 0); 
    exit(EXIT_SUCCESS);

  }
  
  if(pid == -1) {
    handle_syscall_error("FORK FAILED IN RUN_JOB FROM parent"); /*Funciton never returns and shell exits*/
  }

  if(job->background == FALSE) {
    waitpid(pid,&status, 0); /*wait for the  processes to finish */
  }
  
  
}

/**
 * @brief Handles execution of job with multiple stages 
 * 
 * This function executes multiple stages in a pipeline. It sets up 
 * the necessary file descriptors for input and output, and handles piping between 
 * stages. For the first stage, input comes from a file or stdin, and for the final 
 * stage, output is directed to stdout or a file. Intermediate stages transfer data 
 * between pipes.
 * 
 * @param job pointer to the JOB structure containing the pipeline stages.
 * 
 * @return Does not return anything.
 */
static void handle_multi_pipeline_job(JOB *job, char *envp[]) {
  int input_fd, output_fd;
  unsigned int current_stage = 0;
  unsigned int pipe_index = 0;
  int pipes[job->num_stages -1][2];
  
  
  if(pipe(pipes[pipe_index]) == -1) handle_syscall_error("Failed to create Pipe in handle_multi_pipeline_job");
  
  if(initialize_file_descriptors(job, &input_fd, &output_fd) == FALSE) return;
 
 /* The input for the first stage comes from either the infile or stdin, never from a pipe */
 run_command(&job->pipeline[current_stage++],input_fd, pipes[pipe_index][PIPE_WRITE_END], pipes[pipe_index][PIPE_READ_END], envp);

  /* Close the input file if input was redirected */
  if(input_fd != FD_STD_INP) _close(input_fd);

  _close(pipes[pipe_index++][PIPE_WRITE_END]); /*Close after writing to pipe */

  /*Middle stages read from one pipe and write to the next */
  while(current_stage < job->num_stages -1) {
    pipe(pipes[pipe_index]);
    run_command(&job->pipeline[current_stage++], pipes[pipe_index - 1][PIPE_READ_END], pipes[pipe_index][PIPE_WRITE_END], pipes[pipe_index][PIPE_READ_END], envp);
    _close(pipes[pipe_index -1][PIPE_READ_END]); 
    _close(pipes[pipe_index++][PIPE_WRITE_END]);
  }    

  /*Handle last stage, read from the pipe and output to STD out or a file*/
  run_command(&job->pipeline[current_stage], pipes[pipe_index - 1][PIPE_READ_END], output_fd, NO_FD_TO_CLOSE, envp);
  _close(pipes[pipe_index-1][PIPE_READ_END]);

  if(output_fd != FD_STD_OUT) _close(output_fd);

}

/**
 * @brief Handles running a job a with a single pipeline 
 * 
 * This function first initializes the file descriptors based on whether
 * the input is to read from a file and whether output is to redirected to a file.
 * It then uses a helper function which will create a child process to run this command.

 * @param job pointer to the JOB structure containing pipeline and file paths.
 * @return Does not return anything
 */
static void handle_single_pipeline_job(JOB *job, char *envp[]) {
  int input_fd, output_fd;
  
  if(initialize_file_descriptors(job, &input_fd, &output_fd) == FALSE) return;

  run_command(&job->pipeline[0],input_fd, output_fd, NO_FD_TO_CLOSE, envp);

  if(input_fd != FD_STD_INP) _close(input_fd);
  if(output_fd != FD_STD_OUT) _close(output_fd);

}

/**
 * @brief Initializes file descriptors for input and output 
 * 
 * This function opens the input and output files specified in the job struct.
 * If no infile is provided, it defaults to standard input.Similarly,
 * if no outfile is provided, it defaults to standard output
 * 
 * @param job pointer to the JOB structure containing infile and outfile paths.
 * @param input_fd pointer to the input file descriptor to be initialized.
 * @param output_fd pointer to the output file descriptor to be initialized.
 * 
 * @return Returns TRUE on success; otherwise, FALSE if a file could not be opened.
 */
static bool initialize_file_descriptors(JOB *job, int *input_fd, int *output_fd) {
  if(job->infile_path != NULL) {
    *input_fd = open(job->infile_path,O_RDONLY);
    if(*input_fd == -1){
      handle_syscall_error("Could not open infile: ");
      return FALSE;
    }
  } else {
    *input_fd = FD_STD_INP;
  }
  
  if(job->outfile_path != NULL) {
    *output_fd = open(job->outfile_path, O_CREAT | O_RDWR |  O_TRUNC, 0666);
    if(*output_fd == -1){
      handle_syscall_error("Could not open outfile:");
    }
  } else {
    *output_fd = FD_STD_OUT;
  }
  
  return TRUE;
  
}


/**
 * @brief Wrapper for the close system call.Closes the file descriptor
 *        and prints an error message if it fails.
 *
 * @param fd File descripter to be closed
 *
 * @return Does not return anything
 */
static void _close(int fd) {
    if (close(fd) == -1) perror("Error closing file descriptor");
}


/**
 * @brief The function will run a command from the command structure
 *
 * This function will first fork a child process. The child process will then run the
 * command in the command structure. If the provided input file descriptor does not match
 * the standard input, it uses dup2 to redirect standard input to the new fd. Similarly,
 * it performs the same operation for the output file descriptor. Additionally, it will
 * close a file descriptor if specified by `fd_close`. 
 *
 * If fork, execve, close, or dup2 fails, it will print an error message.
 *
 * @param command pointer to the Command structure containing the command attributes
 * @param input_fd file descriptor for input redirection 
 * @param output_fd file descriptor for output redirection
 * @param fd_close File descriptor to be closed in the child process, 
 *                 or -1 if no fd needs to be closed.
 *
 * @return Does not return anything.
 */
static void run_command(Command *command, int input_fd, int output_fd, int fd_close, char *envp[]) {
  pid_t pid = fork();
  
  if(pid == 0)
    {
   signal(SIGINT, SIG_DFL);
   
   if(input_fd != FD_STD_INP) {
      redirect_fd(FD_STD_INP,input_fd);
    }
    
    if(output_fd != FD_STD_OUT) {
      redirect_fd(FD_STD_OUT,output_fd);
    }
    
    if(fd_close != -1) {
      _close(fd_close);
    }
    
    execve(command->argv[0], command->argv, envp);
    perror("Error running process");    
    _exit(-1);
    
  } else if(pid == -1){
    perror("Fork failed in run command");    
    return;
  }
  
  
}

/**
 * @brief Redirects  old file descriptor to a new one
 *
 * @param old_fd file descriptor to be replaced.
 * @param new_fd ile descriptor to be duplicated to old_fd.
 
 * @return Does not return anything
 */
static void redirect_fd(int old_fd, int new_fd){
  if(dup2(new_fd,old_fd) == -1) {
    perror("Dup2 in redirect_fd Failed");
    exit(-1);
  }
  
  if(close(new_fd) == -1){
    perror("Close in redirect_fd Failed");
    exit(-1);
  }
}
