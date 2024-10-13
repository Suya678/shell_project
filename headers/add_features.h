
#ifndef ADD_FEATURES
#define ADD_FEATURES
#include <sys/stat.h>
#include "parser.h"
#include "our_string.h"
#include "error_handlers.h"

void my_cd(JOB *job);
void resolve_command_path(JOB *job, char *envp[]);
void signal_child_setup();
void signal_int_setup();

#endif
