
#ifndef ADD_FEATURES
#define ADD_FEATURES
#include <sys/stat.h>
#include "parser.h"
#include "our_string.h"
bool _chdir(JOB *job);
void resolve_command_path(JOB *job, char *envp[]);

#endif
