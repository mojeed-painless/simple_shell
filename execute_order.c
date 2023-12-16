#include "shell.h"

/**
  * execute_order - executes a file.
  * @order: executed command.
  */

void execute_order(const char *order)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		mjd_display("Error forking process.\n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		char *args[130];
		int arg_c = 0;

		char *token = strtok((char *)order, " ");
		while (token != NULL)
		{
			args[arg_c++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_c] = NULL;

		execvp(args[0], args);

		mjd_display("Error executing command.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}
