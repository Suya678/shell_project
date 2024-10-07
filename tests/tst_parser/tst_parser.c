#include <stdio.h>

#include "parser.h"
void print_command_args(JOB *job);


int main() {


  JOB job;


    get_usr_input(&job.usr_input);
    
    if(validate_and_parse_job(&job) == FALSE) {
        printf("REJECTED\n");
    }

    print_command_args(&job);


    
    


}


void print_command_args(JOB *job) {
  Command *current_command;
    for (unsigned int i = 0; i < job->num_stages; i++) {
        printf("Command %d: ", i + 1);
        current_command  = &job->pipeline[i];
        for (unsigned int j = 0; current_command->argv[j] != NULL; j++) {
            printf("%s ", current_command->argv[j]);
        }
        printf("\n"); 
    }
}
