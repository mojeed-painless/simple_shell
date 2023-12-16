#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

void execute_order(const char *order);
void mjd_display(const char *memo);
void show_prompt(void);
void read_order(char *order, size_t size);

#endif /* SHELL_H */
