#include <stdio.h>

#include "parser.h"
void print_command_args(JOB *job);


void CASE_ACCEPTS_1_PIPELINE_VALID_COMMAND();
void CASE_ACCEPTS_2_PIPELINE_VALID_COMMAND();
void CASE_REJECTS_1_PIPELINE_INVALID_COMMAND();
void CASE_REJECTS_2_PIPELINE_INVALID_COMMAND();

int main() {

  printf("TESTING VALIDATE AND PARSE JOB FUNCTIONALITY \nPress enter to continue\n");
  getchar();
  CASE_ACCEPTS_1_PIPELINE_VALID_COMMAND();
  CASE_REJECTS_1_PIPELINE_INVALID_COMMAND();  

  CASE_ACCEPTS_2_PIPELINE_VALID_COMMAND();
  CASE_REJECTS_2_PIPELINE_INVALID_COMMAND();

}



void CASE_ACCEPTS_1_PIPELINE_VALID_COMMAND(){
  JOB job;
  
  printf("TESTING IF A VALID 1 PIPELINE COMMAND IS ACCEPTED AND JOB IS POPUlATED PROPERLY \nPress enter to continue\n");
  getchar();

  printf("Case 1: Please enter 1 pipeline without any flags (EX: /bin/ls) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);


  printf("Case 2: Please enter 1 pipeline with 1 flags (EX: /bin/ls - l) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);

  printf("Case 3: Please enter 1 pipeline with multiple flags  (EX: /bin/ls -l - k -l - l -t -p -k) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);

  printf("Case 4: Please enter 1 pipeline with input redirection   (EX: /bin/ls < kl) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);
  
  printf("Case 5: Please enter 1 pipeline with output redirection   (EX: /bin/ls > kl) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);

  printf("Case 6: Please enter 1 pipeline with background processing enabled   (EX: /bin/ls &) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);

  printf("Case 7: Please enter 1 pipeline with input redirection, output redirection\nand background processing enabled  (EX: /bin/ls < kl > l &) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);

}



void CASE_REJECTS_1_PIPELINE_INVALID_COMMAND(){

  JOB job;
  printf("TESTING IF A INVALID 1 PIPELINE COMMAND IS REJECTED\nPress enter to continue\n");
  getchar();

  printf("Case 1: Please enter 1 pipeline begining with &  (EX: & /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }

  printf("Case 2: Please enter 1 pipeline begining with >  (EX: > /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }

  
  printf("Case 3: Please enter 1 pipeline begining with < (EX: < /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }


  printf("Case 4: Please enter 1 pipeline begining with |  (EX: | /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }
  
  printf("Case 5: Please enter 1 pipeline begining with multiple < (EX: < < < /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }

  
  printf("Case 6: Please enter 1 pipeline begining with multiple < & > | (EX: < & > < > & | /bin/ls) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }

  printf("Case 7: Please enter 1 pipeline with input redirection but not specifyiing the file | (EX: /bin/ls < ) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }
  
  printf("Case 8: Please enter 1 pipeline with output redirection but not specifying the file | (EX: /bin/ls > ) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }
  
  
  
  printf("Case 9: Please enter 1 pipeline with background flag and a token after it as well  | (EX: /bin/ls & ss ) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }
  
}





void CASE_ACCEPTS_2_PIPELINE_VALID_COMMAND(){
  JOB job;
  printf("TESTING IF A VALID 2 PIPELINE JOB IS ACCEPTED ANDPOPUlATED PROPERLY \nPress enter to continue\n");

  getchar();
  printf("\n");
  
  printf("Case 1: Please enter 2 pipeline without any flags (EX: /bin/ls | /bin/usr) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);

  printf("Case 2: Please enter 2 pipeline with 1 flags (EX: /bin/ls - l | /bin/usr lk) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);

  printf("Case 3: Please enter 2 pipeline with input redirection   (EX: /bin/ls -kl | bin/usr < ss) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);

  printf("Case 4: Please enter 2 pipeline with output redirection   (EX: /bin/ls -kl | bin/usr > ss) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);

  printf("Case 5: Please enter 2 pipeline with background processing enabled   (EX: /bin/ls | /bin/usr &) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);

  printf("Case 6: Please enter 2 pipeline with input redirection, output redirection\nand background processing enabled  (EX: /bin/ls | bin/usr < kl > l &) \n");
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  print_command_args(&job);
  printf("\n");

}


void CASE_REJECTS_2_PIPELINE_INVALID_COMMAND(){


  JOB job;
  printf("TESTING IF A INVALID 2 PIPELINE COMMAND IS REJECTED\nPress enter to continue\n");
printf("\n");

  getchar();

  printf("Case 1: Please enter 2 pipeline begining but not specifying the second command (EX: /bin/ls | ) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }

  printf("Case 2: Please enter 2 pipeline but start the second command with a special symbol\n(EX: /bin/ls | & ss) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }
  

  printf("Case 3: Please enter 2 pipeline end it with the input redirection\nsymbol without specifying the file path(EX: /bin/ls | usr < ) \nIt should be Rejected\n");
  get_usr_input(&job.usr_input);
  if(validate_and_parse_job(&job) == FALSE) {
    printf("THis command was rejected\n");
  } else {
    printf("THis command was accepted\n");
  }

    printf("Case 3: Please enter 2 pipeline end it with the output redirection\nsymbol without specifying the file path(EX: /bin/ls | usr > ) \nIt should be Rejected\n");
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

    if(job->infile_path != NULL){
      printf("Input redirection requested, file path: %s ", job->infile_path);
    } else{
      printf("No input redirection ");
    }
      printf("\n"); 

      if(job->outfile_path != NULL){
          printf("Output redirection requested, file path: %s", job->outfile_path);
        } else {
          printf("No output redirection ");
        }
        printf("\n"); 

         if(job->background == TRUE){
          printf("BACKGROUND processing activated ");
        } else {
          printf("BACKGROUND processing not activated ");
        }
        printf("\n"); 


}
