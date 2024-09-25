
#include <unistd.h>
#include <fcntl.h>
#include "cmd_handler.h"
#include "our_string.h"
#include <stdio.h>
int main(char argc, char *argv[]) {
  Command command;
  int index = 0;
  do {
    get_command(&command);
    /*    while(command.argv[index] != NULL) {
	printf("%s\n", command.argv[index++]);
      }
    index = 0;
    */
    execve(command.argv[0], command.argv, NULL);
  }while(string_compare(command.usr_input, "exit", 4) != TRUE);


  return 0;
}
