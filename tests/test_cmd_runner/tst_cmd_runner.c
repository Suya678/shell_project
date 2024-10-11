#include <stdio.h>
#include "cmd_runner.h"
#include "parser.h"

/*
void CASE_SINGLE_PIPELINE_JOB();
void CASE_MULTI_PIPELINE_JOBS();
void CASE_BACKGROUND_JOBS();
void CASE_ERROR_CASES();
void CASE_REDIRECTION_ERRORS();
*/
void CASE_ZOMBIE_KILLER_FAIL();
void CASE_ZOMBIE_KILLER_SUCCESS();

int main() {

  printf("TESTING COMMAND RUNNER FUNCTIONALITY\nPress enter to continue\n");
  getchar();
  /*
  CASE_SINGLE_PIPELINE_JOB();
  CASE_MULTI_PIPELINE_JOBS();
  CASE_BACKGROUND_JOBS();
  CASE_ERROR_CASES();  
  CASE_REDIRECTION_ERRORS();
  */
  CASE_ZOMBIE_KILLER_FAIL();
  CASE_ZOMBIE_KILLER_SUCCESS();
  printf("JOB RUNNER TESTS COMPLETE\n");

  return 0;
}


void CASE_SINGLE_PIPELINE_JOB(){
  JOB ls_job;
  JOB cat_job;
  //hard coding job struct
  ls_job.pipeline[0].argv[0] = "/bin/ls";
  ls_job.pipeline[0].argv[1] = NULL;
  ls_job.num_stages = 1;
  ls_job.outfile_path = NULL;
  ls_job.infile_path = NULL;
  ls_job.background = FALSE;

  cat_job.pipeline[0].argv[0] = "/bin/cat";
  cat_job.pipeline[0].argv[1] = "../../headers/cmd_runner.h";
  cat_job.pipeline[0].argv[2] = NULL;
  cat_job.num_stages = 1;
  cat_job.outfile_path = NULL;
  cat_job.infile_path = NULL;
  cat_job.background = FALSE;

  printf("BEGINNING SINGLE PIPELINE JOB TESTS\n\n");
  printf("Running a simple command\n\n");
  printf("TESTING LS -press enter\n");
  getchar();
  run_job(&ls_job, NULL);

  printf("\nTESTING CAT with ../../headers/cmd_runner.h -press enter\n");
  getchar();
  run_job(&cat_job, NULL);
  printf("\n\n");

  printf("Command with input redirection\n\n");
  cat_job.pipeline[0].argv[1] = NULL;
  cat_job.infile_path = "./infile.txt";
  printf("TESTING CAT infile.txt -press enter\n");
  getchar();
  run_job(&cat_job, NULL);

  printf("Command with output redirection\n\n");
  ls_job.outfile_path = "./outfile.txt";
  printf("TESTING LS outfile.txt -press enter\n");
  getchar();
  run_job(&ls_job, NULL);
  printf("check outfile.txt\n");
  printf("\n\n");

  printf("Command with both input and output redirection\n\n");
  cat_job.outfile_path = "./outfile.txt";
  cat_job.infile_path = "./infile.txt";
  printf("TESTING cat < infile.txt > outfile.txt -press enter\n");
  getchar();
  run_job(&cat_job, NULL);
  printf("check outfile.txt\n");
  printf("\n\n");

}


void CASE_MULTI_PIPELINE_JOBS(){
  JOB pipeline_job;
  pipeline_job.num_stages = 2;
  pipeline_job.background = FALSE;

  //first stage
  pipeline_job.pipeline[0].argv[0] = "/bin/ls";
  pipeline_job.pipeline[0].argv[1] = NULL;
  pipeline_job.pipeline[0].argc = 1;

  //second stage
  pipeline_job.pipeline[1].argv[0] = "/bin/grep";
  pipeline_job.pipeline[1].argv[1] = "infile.txt";
  pipeline_job.pipeline[1].argv[2] = NULL;
  pipeline_job.pipeline[1].argc = 2;

  pipeline_job.infile_path = NULL;
  pipeline_job.outfile_path = NULL;

  printf("BEGINNING MULTI PIPELINE JOBS TESTS\n\n");
  printf("Running a simple pipeline\n\n");
  printf("TESTING ls | grep infile.txt\n");
  //getchar
  run_job(&pipeline_job, NULL);
  printf("\n\n");

  printf("Running a 3 stage pipeline with input and output redirection\n\n");
  printf("TESTING cat infile.txt | grep 'never' | sort - press enter\n");
  pipeline_job.num_stages = 3;
  //first stage
  pipeline_job.pipeline[0].argv[0] = "/bin/cat";
  pipeline_job.pipeline[0].argv[1] = "./infile.txt";
  pipeline_job.pipeline[0].argv[2] = NULL;
  pipeline_job.pipeline[0].argc = 2;
   //second stage
  pipeline_job.pipeline[1].argv[0] = "/bin/grep";
  pipeline_job.pipeline[1].argv[1] = "never";
  pipeline_job.pipeline[1].argv[2] = NULL;
  pipeline_job.pipeline[1].argc = 2;
   //third stage
  pipeline_job.pipeline[2].argv[0] = "/bin/sort";
  pipeline_job.pipeline[2].argv[1] = NULL;
  pipeline_job.pipeline[2].argc = 1;

  pipeline_job.infile_path = "./infile.txt";
  pipeline_job.outfile_path = "./outfile.txt";
 
  getchar();
  run_job(&pipeline_job, NULL);
  printf("check outfile.txt\n");

}


void CASE_BACKGROUND_JOBS(){
  JOB sleep_job;
  //hard coding job struct
  sleep_job.pipeline[0].argv[0] = "/bin/sleep";
  sleep_job.pipeline[0].argv[1] = "5";
  sleep_job.pipeline[0].argv[2] = NULL;
  sleep_job.num_stages = 1;
  sleep_job.outfile_path = NULL;
  sleep_job.infile_path = NULL;
  sleep_job.background = FALSE;
  printf("BEGINNING BACKROUND TESTS\n");
  printf("Running a simple command in the background\n\n");
  printf("TESTING sleep 5 - press enter (not in background)\n");
  run_job(&sleep_job, NULL);
  getchar();
  printf("TESTING sleep 5 &- press enter (in background)\n");
  sleep_job.background = TRUE;
  run_job(&sleep_job, NULL);
  getchar();
  
  printf("\n\n");
  printf("Running a pipeline in the background\n\n");

  JOB pipeline_job;
  pipeline_job.num_stages = 2;
  pipeline_job.background = TRUE;

  //first stage
  pipeline_job.pipeline[0].argv[0] = "/bin/ls";
  pipeline_job.pipeline[0].argv[1] = NULL;
  pipeline_job.pipeline[0].argc = 1;

  //second stage
  pipeline_job.pipeline[1].argv[0] = "/bin/grep";
  pipeline_job.pipeline[1].argv[1] = "infile.txt";
  pipeline_job.pipeline[1].argv[2] = NULL;
  pipeline_job.pipeline[1].argc = 2;

  pipeline_job.infile_path = NULL;
  pipeline_job.outfile_path = NULL;


  printf("TESTING ls | grep infile.txt &\n");
  run_job(&pipeline_job, NULL);
  printf("\n\n");
}


void CASE_ERROR_CASES(){
  JOB automaticA_job;
  automaticA_job.pipeline[0].argv[0] = "/bin/automaticA";
  automaticA_job.pipeline[0].argv[1] = NULL;
  automaticA_job.num_stages = 1;
  automaticA_job.outfile_path = NULL;
  automaticA_job.infile_path = NULL;
  automaticA_job.background = FALSE;
  printf("BEGINNING ERROR CASES TESTS\n");
  printf("running an invalid command\n");
  printf("TESTING automaticA - press enter\n");
  getchar();
  run_job(&automaticA_job, NULL);
  printf("\n\n");

  JOB pipeline_illegal;
  pipeline_illegal.num_stages = 2;
  pipeline_illegal.background = FALSE;

  //first stage
  pipeline_illegal.pipeline[0].argv[0] = "/bin/ls";
  pipeline_illegal.pipeline[0].argv[1] = NULL;
  pipeline_illegal.pipeline[0].argc = 1;

  //second stage
  pipeline_illegal.pipeline[1].argv[0] = "/bin/automaticA";
  pipeline_illegal.pipeline[1].argv[1] = NULL;
  pipeline_illegal.pipeline[1].argc = 1;

  pipeline_illegal.infile_path = NULL;
  pipeline_illegal.outfile_path = NULL;

  printf("running a pipeline with an invalid command\n");
  printf("TESTING ls | automaticA - press enter\n");
  getchar();
  run_job(&pipeline_illegal, NULL);
  printf("\n\n");
}


void CASE_REDIRECTION_ERRORS(){
  JOB midtermAns_job;
  //hard coding job struct
  midtermAns_job.pipeline[0].argv[0] = "/bin/cat";
  midtermAns_job.pipeline[0].argv[1] = NULL;
  midtermAns_job.num_stages = 1;
  midtermAns_job.outfile_path = NULL;
  midtermAns_job.infile_path = "./OSmidtermANSWERS.TXT";
  midtermAns_job.background = FALSE;
  printf("BEGINNING REDIRECTION ERRORS\n");
  printf("input redirection from non existant file\n");
  printf("TESTING cat < OSmidtermANSWERS.TXT -press enter\n");
  getchar();
  run_job(&midtermAns_job, NULL);
  printf("\n\n");
}

void CASE_ZOMBIE_KILLER_FAIL(){

  printf("BEGINNING ZOMBIE CHILDREN TESTS WITHOUT SIGNAL HANDLING\n");

  pid_t pid = fork();
  if(pid < 0){
    perror("fork failed");
    exit(1);
  }
  if(pid == 0){
    printf("\tchild simulating work\n");
    sleep(3);
    printf("\tchild exiting\n");
    exit(0);
  } else {
    printf("\tparent waiting on child\n");
    sleep(20);
    printf("\tparent done waiting\n");
  }

}

void CASE_ZOMBIE_KILLER_SUCCESS(){
  struct sigaction sa;
  sa.sa_handler = signal_child_handler; //in cmd_runner.c
  sigemptyset(&sa.sa_mask);        // Initialize an empty set *i got this from chatgpt it says we need it for predictability*

  if (sigaction(SIGCHLD, &sa, NULL) == -1) { //SIGCHLD is child stopped or terminated
    perror("sigaction");
    return;
  }
  
  printf("\n\nBEGINNING ZOMBIE CHILDREN TESTS WITH SIGNAL HANDLING\n");

  pid_t pid = fork();
  if(pid < 0){
    perror("fork failed");
    exit(1);
  }
  if(pid == 0){
    printf("\tchild simulating work\n");
    sleep(3);
    printf("\tchild exiting\n");
    exit(0);
  } else {
    printf("\tparent waiting on child\n");
    sleep(20);
    printf("\tparent done waiting\n");
  }

}