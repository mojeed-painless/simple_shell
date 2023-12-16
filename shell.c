#include "shell.h"

/**
  * main - Entry point.
  * Return: always 0.
  */

int main(void)
{
	char order[130];

	while (1)
	{
		show_prompt();
		read_order(order, sizeof(order));
		execute_order(order);
	}

	return (0);
}
