
#include <unistd.h>
#include <fcntl.h>
#include "parser.h"
#include "cmd_runner.h"
#include "our_string.h"
#include <stdio.h>


int main(char argc, char *argv[], char *envp[]) {
  USR_INP usr_inp;
  unsigned int num = 0;
  get_usr_input(&usr_inp);



  while(num < usr_inp.num_tokens){
    printf("%s\n",usr_inp.argv[num]);
    num++;
  }

  return 0;
}
