
#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <errno.h>

#include <stddef.h>
#include <stdlib.h>
#include "our_string.h"
void handle_write_error();
void handle_read_error();
void handle_syscall_error(char *str);

#endif