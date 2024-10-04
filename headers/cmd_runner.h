#ifndef CMD_RUNNER
#define CMD_RUNNER


#include "parser.h"


void check_for_background_processing(Command *command);
void run_command(Command *command);

#endif