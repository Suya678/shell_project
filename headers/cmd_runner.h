#ifndef CMD_RUNNER
#define CMD_RUNNER


#include "parser.h"

#define READ_MODE 0
#define WRITE_MODE 1

#define PIPE_READ_END 0
#define PIPE_WRITE_END 1
#define NO_FD_TO_CLOSE -1
void check_for_background_processing(Command *command);
void run_command(Command *command, int input_fd, int output_fd, int fd_close, char *envp[]);
void run_job(JOB *job, char *envp[]);
void redirect_fd(int old_fd, int new_fd);
void _close(int fd);
int open_file(char *file_path, int mode);
void handle_multi_pipeline_job(JOB *job, char *envp[]);
void handle_single_pipeline_job(JOB *job, char *envp[]);
bool initialize_file_descriptors(JOB *job, int *input_fd, int *output_fd);
#endif