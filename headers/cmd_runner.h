#ifndef CMD_RUNNER_H
#define CMD_RUNNER_H
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parser.h"
#include "signal.h"
#include "bool.h"
#include "error_handlers.h"


void run_job(JOB *job, char *envp[]);


#endif