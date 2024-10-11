#ifndef CMD_RUNNER
#define CMD_RUNNER
#include "parser.h"
void run_job(JOB *job, char *envp[]);
void signal_child_setup();

#endif