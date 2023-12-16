#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **enviro;
char *name;
int histo;

void execute_order(const char *order);
void mjd_display(const char *memo);
void show_prompt(void);
void read_order(char *order, size_t size);

/**
 * struct builtin_s - A new struct.
 * @name: The name of the builtin.
 * @funct: A function pointer.
 */
typedef struct builtin_s
{
	char *name;
	int (*funct)(char **argv, char **front);
} builtin_t;

/**
 * struct list_s - A new struct type.
 * @direct: A directory.
 * @next: A pointer.
 */
typedef struct list_s
{
	char *direct;
	struct list_s *next;
} list_t;

/**
 * struct alias_s - A new struc.
 * @name: The name of alias.
 * @val: The value of the alias.
 * @next: A pointer.
 */
typedef struct alias_s
{
	char *name;
	char *val;
	struct alias_s *next;
} alias_t;

alias_t *aliases;

int proc_file_commands(char *file_path, int *exe_ret);

/* Linkedlist aiders */
alias_t *add_alias_end(alias_t **head, char *name, char *val);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *direct);
void free_list(list_t *head);

void aid_all(void);
void aid_alias(void);
void aid_cd(void);
void aid_exit(void);
void aid_help(void);
void aid_env(void);
void aid_setenv(void);
void aid_unsetenv(void);
void aid_history(void);

/* Flaw Handling */
int create_flaw(char **args, int err);
char *flaw_env(char **args);
char *flaw_1(char **args);
char *flaw_2_exit(char **args);
char *flaw_2_cd(char **args);
char *flaw_2_syntax(char **args);
char *flaw_126(char **args);
char *flaw_127(char **args);

/* Builtin aiders */
char **copy_env(void);
void free_env(void);
char **get_env(const char *var);

/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_alias(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);

/* String functions */
int str_len(const char *s);
char *str_cat(char *dest, const char *src);
char *str_ncat(char *dest, const char *src, size_t n);
char *str_cpy(char *dest, const char *src);
char *str_chr(char *s, char c);
int str_spn(char *s, char *accept);
int str_cmp(char *s1, char *s2);
int str_ncmp(const char *s1, const char *s2, size_t n);

/* Input aiders */
void handle_line(char **line, ssize_t read);
void variable_replace(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_arg(char **args, char **front, int *exe_ret);
int run_arg(char **args, char **front, int *exe_ret);
int handle_arg(int *exe_ret);
int check_arg(char **args);
void free_arg(char **args, char **front);
char **replace_aliase(char **args);

/* Main aiders */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);

#endif /* SHELL_H */
