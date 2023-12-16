#include "shell.h"

/**
  * read_order - Reads command from user.
  * @order: command from user.
  * @size: size of input.
  */

void read_order(char *order, size_t size)
{
	if (fgets(order, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			mjd_display("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			mjd_display("Error on input.\n");
			exit(EXIT_FAILURE);
		}
	}
	order[strcspn(order, "\n")] = '\0';
}
