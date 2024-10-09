#include "cmd_runner.h"

void handle_multi_pipeline_job(JOB *job) {
  int input_fd = FD_STD_INP, output_fd = FD_STD_OUT;
  unsigned int num_pipes = 0;
  int pipes[job->num_stages][2];

  pipe(pipes[num_pipes]);

  if(job->outfile_path != NULL) {
    if((output_fd = open_file(job->outfile_path, -1)) == -1) return;
  }

  if(job->infile_path != NULL){
    if((input_fd = open_file(job->infile_path, READ_MODE)) == -1) return;
  }

  run_command(&job->pipeline[0],input_fd, pipes[num_pipes][PIPE_WRITE_END]);

  if(input_fd != FD_STD_INP) _close(input_fd);

  close(pipes[num_pipes++][PIPE_WRITE_END]);

  while(num_pipes < job->num_stages -1) {
    pipe(pipes[num_pipes]);
    run_command(&job->pipeline[1],pipes[num_pipes - 1][PIPE_READ_END], pipes[num_pipes][PIPE_WRITE_END]);
    close(pipes[num_pipes -1 ][PIPE_READ_END]);
    close(pipes[num_pipes][PIPE_WRITE_END]);
    num_pipes++;
  }    

  run_command(&job->pipeline[1],pipes[num_pipes - 1][PIPE_READ_END], output_fd);
  close(pipes[num_pipes][1]);
  if(output_fd != FD_STD_OUT) _close(output_fd);


}


void handle_single_pipeline_job(JOB *job) {
  int input_fd = FD_STD_INP, output_fd = FD_STD_OUT;
  pid_t pid;
 
  if(job->outfile_path != NULL) {
    if((output_fd = open_file(job->outfile_path, -1)) == -1) return;
  }

  if(job->infile_path != NULL){
    if((input_fd = open_file(job->infile_path, READ_MODE)) == -1) return;
  }

  run_command(&job->pipeline[0],input_fd, output_fd);

  if(input_fd != FD_STD_INP) _close(input_fd);
  if(output_fd != FD_STD_OUT) _close(output_fd);
}


/**
 * @brief Opens the file provided in the file path and mode. Returns the file descriptor or -1 on aerror
 *
 * @param file_path file to be opened
 * @param mode decides whether to open the file for reading or writing(0 for read and any other number for writing)

 * @return retuns the fd of the opened file. IF a error is encountered, it prints an error
           message and return -1
 */
int open_file(char *file_path, int mode){

  int file_fd;

  if(mode == READ_MODE) {
   file_fd = open(file_path,O_RDONLY);
    if(file_fd == -1) {
      perror("Could not open infile: ");
      return -1;
    }
  } else {
    file_fd = open(file_path, O_CREAT | O_RDWR |  O_TRUNC, 0666);
     if(file_fd == -1) {
      perror("Could not open outfile: ");
      return -1; 
    }
  }

  return file_fd;
}



/**
 * @brief Wrapper for the close system call.Closes the file descriptor
 *        and prints an error message if it fails.
 *
 * @param fd File descripter to be closed
 *
 * @return Does not return anything
 */
void _close(int fd) {
    if (close(fd) == -1) perror("Error closing file descriptor");
}


/**
 * @brief The funcition will run a command from the command strucuture
 *
 * This function will first fork a child process. The child process will then run the
 * commadn in the command structure.If the provided input file descriptor does not match
 *  the standard input, it uses dup2 to redirect standard input to the new fd.
 * Similarly, it performs the same operation for the output file descriptor.
 * If fork, execve, close or dupe2 fails, it will print an error message
 *
 * @param Command *command structure containing the command attributes 
 *
 * @return Does not return anything
 */
void run_command(Command *command, int input_fd, int output_fd) {
  pid_t pid = fork();

  if(pid == 0)
  {
    if(input_fd != FD_STD_INP) {
      redirect_fd(FD_STD_INP,input_fd);
    }

    if(output_fd != FD_STD_OUT) {
      redirect_fd(FD_STD_OUT,output_fd);
    }

    execve(command->argv[0], command->argv, NULL);
    perror("Error running process: ");    
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
void redirect_fd(int old_fd, int new_fd){
   if(dup2(new_fd,old_fd) == -1) {
        perror("Dup2 in redirect Failed");
        exit(-1);
    }

    if(close(new_fd) == -1){
        perror("Close in redirect_fd Failed");
        exit(-1);
    }
}
