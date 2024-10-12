
#ifndef PARSER_H
#define PARSER_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "our_string.h"
#include "bool.h"


#define FD_STD_INP 0
#define FD_STD_OUT 1
#define MAX_SIZE 256
#define FD_STD_ERR 2


#define MAX_PIPELINE_LEN 128
#define MAX_ARGS 128




typedef struct Command
{
  char *argv[MAX_ARGS+1];   
  unsigned int argc;
} Command;


/*
 Holds the user input as well as pointers to each individual tokena and the number of tokens
 */
typedef struct USR_INP
{
  char usr_input[MAX_SIZE];
  char *argv[MAX_ARGS+1];   
  unsigned int num_tokens;
} USR_INP;


typedef struct JOB
{
    USR_INP usr_input;
    Command pipeline[MAX_PIPELINE_LEN];
    unsigned int num_stages;
    char *outfile_path;          /* NULL for no output redirection     */
    char *infile_path;           /* NULL for no input redirection      */
    bool background;              /* 0=foreground, otherwise=background */
} JOB;


void get_usr_input(USR_INP *usr_inp);
void flush_std_input_buffer();

bool validate_and_parse_job(JOB *job);
#endif
