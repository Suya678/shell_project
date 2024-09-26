
#include <unistd.h>
#include <fcntl.h>
#include "cmd_handler.h"
#include "our_string.h"
#include <stdio.h>
int main(char argc, char *argv[]) {
  Command command;
  get_command(&command);

  while(string_compare(command.argv[0], "exit", 0) == FALSE)
    {
      check_for_background_processing(&command);
      run_command(&command);
      get_command(&command);
    }
  
  return 0;
}
