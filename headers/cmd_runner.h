#ifndef CMD_RUNNER_H
#define CMD_RUNNER_H
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parser.h"
#include "signal.h"
#include "bool.h"


void run_job(JOB *job, char *envp[]);
void signal_child_setup();

#endif