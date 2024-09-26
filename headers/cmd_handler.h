#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef CMD_HANDLER
#define CMD_HANDLER


#define FD_STD_INP 0
#define FD_STD_OUT 1
#define MAX_SIZE 256
#define FD_STD_ERR 2
#define FALSE 0
#define TRUE 1

#define MAX_ARGS 128

typedef int bool;

typedef struct Command
{
  char usr_input[MAX_SIZE];
  char *argv[MAX_ARGS+1];   
  unsigned int argc;
  bool process_in_background;
} Command;

void check_for_background_processing(Command *command);
void get_command(Command *command);
void run_command(Command *command);
void flush_input_string(char str[]);
void flush_std_input_buffer();
void print_string(char *to_print);
bool string_compare(char *str1, char *str2, int num_chars);  
bool is_string_empty(char string[]);
void string_tokenizer(char *to_decompose, char *tokens[], unsigned int *num_tokens);
#endif
