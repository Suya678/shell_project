#include <unistd.h>
#include <fcntl.h>


#define FD_STD_INP 0
#define FD_STD_OUT 1
#define MAX_SIZE 257
#define FALSE 0
#define TRUE 1

typedef int bool;

void read_usr_inp(char usr_inp[]) ;
void flush_input_string(char str[]);
void flush_std_input_buffer();
void print_string(char *to_print);
bool string_compare(char *str1, char *str2, int num_chars);  
