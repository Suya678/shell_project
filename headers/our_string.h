
#ifndef OUR_STRING_H
#define OUR_STRING_H

#include "parser.h"
#include "bool.h"
void print_string(char *to_print);
bool string_compare(char *str1, char *str2, int num_chars);  
void my_str_cat(char *source, char *destination);
void string_copy(char *source, char *destination, char delimiter);
bool is_string_empty(char string[]);

#endif
