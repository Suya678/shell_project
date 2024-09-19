#include <unistd.h>
#define FD_STD_INP 0
#define FD_STD_OUT 1
#define MAX_SIZE 257
void read_usr_inp(char usr_inp[]) ;
void flush_input_string(char str[]);
void flush_std_input_buffer();
void print_string(char *to_print);
