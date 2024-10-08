#include <stdio.h>

#include "parser.h"
void print_command_args(JOB *job);


void CASE_ACCEPTS_1_PIPELINE_VALID_COMMAND();

void CASE_ACCEPTS_1_PIPELINE_INVALID_COMMAND();


int main() {

  printf("TESTING VALIDATE AND PARSE JOB FUNCTIONALITY \nPress enter to continue\n");
  getchar();
 /* CASE_ACCEPTS_1_PIPELINE_VALID_COMMAND();*/

  
  CASE_ACCEPTS_1_PIPELINE_INVALID_COMMAND();
    


}



void CASE_ACCEPTS_1_PIPELINE_VALID_COMMAND(){


  JOB job;
  printf("TESTING IF A VALID 1 PIPELINE COMMAND IS ACCEPTED AND JOB IS POPUlATED PROPERLY \nPress enter to continue\n");


  getchar();

  printf("Case 1: Plesae enter 1 pipeline without any flags (EX: /bin/ls) \n");

  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);


  printf("Case 2: Plesae enter 1 pipeline with 1 flags (EX: /bin/ls - l) \n");

  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);



  printf("Case 3: Plesae enter 1 pipeline with multiple flags  (EX: /bin/ls -l - k -l - l -t -p -k) \n");

  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);



  

}



void CASE_ACCEPTS_1_PIPELINE_INVALID_COMMAND(){


  JOB job;
  printf("TESTING IF A INVALID 1 PIPELINE COMMAND IS REJECTED\nPress enter to continue\n");


  getchar();

  printf("Case 1: Plesae enter 1 pipeline begining with &  (EX: & /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }

  printf("Case 2: Plesae enter 1 pipeline begining with >  (EX: > /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }
  



  printf("Case 3: Plesae enter 1 pipeline begining with < (EX: < /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }


  printf("Case 4: Plesae enter 1 pipeline begining with |  (EX: | /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }
  


  printf("Case 5: Plesae enter 1 pipeline begining with multiple < (EX: < < < /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }


  printf("Case 6: Plesae enter 1 pipeline begining with multiple < & > | (EX: < & > < > & | /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }




  printf("Case 7: Plesae enter 1 pipeline with input redirection but not specifyiing the file | (EX: /bin/ls > ) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }

  printf("Case 8: Plesae enter 1 pipeline with output redirection but not specifying the file | (EX: /bin/ls < ) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }



  printf("Case 9: Plesae enter 1 pipeline with background flag and a token after it as well  | (EX: /bin/ls & ss ) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }





}

void print_command_args(JOB *job) {
  Command *current_command;
    printf("You entered: \n");
    for (unsigned int i = 0; i < job->num_stages; i++) {
        printf("Command %d: ", i + 1);
        current_command  = &job->pipeline[i];
        for (unsigned int j = 0; current_command->argv[j] != NULL; j++) {
            printf("%s ", current_command->argv[j]);
        }
        printf("\n"); 
    }
}
