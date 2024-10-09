
#ifndef PARSER
#define PARSER

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


#define FD_STD_INP 0
#define FD_STD_OUT 1
#define MAX_SIZE 256
#define FD_STD_ERR 2
#define FALSE 0
#define TRUE 1

#define MAX_PIPELINE_LEN 128
#define MAX_ARGS 128

typedef int bool;



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









void check_command_syntax(USR_INP *usr_inp);



void get_usr_input(USR_INP *usr_inp);
void flush_input_string(char str[]);
void flush_std_input_buffer();
void print_string(char *to_print);
bool string_compare(char *str1, char *str2, int num_chars);  
bool is_string_empty(char string[]);
void string_tokenizer(char *to_decompose, char *tokens[], unsigned int *num_tokens);






bool validate_and_parse_job(JOB *job);

void read_pipeline(JOB *job, bool *valid_input,  unsigned int *token_counter);

bool is_special_symbol(char *str);
void handle_pipe(JOB *job, bool *valid_input, unsigned int *token_counter);

void handle_background_symbol(JOB *job, bool *valid_input, unsigned int *token_counter);



void handle_input_redirection(JOB *job, bool *valid_input, unsigned int *token_counter);
void handle_output_redirection(JOB *job, bool *valid_input, unsigned int *token_counter);

#endif
