#include "shell.h"

/**
 * mjd_display - prints standard output.
 * @memo: message to display.
 */

void mjd_display(const char *memo)
{
	write(STDOUT_FILENO, memo, strlen(memo));
}
