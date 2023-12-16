#include "shell.h"

char **copy_env(void);
void free_env(void);
char **get_env(const char *var);

/**
 * copy_env - Creates a copy.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **copy_env(void)
{
	char **new_enviro;
	size_t size;
	int index;

	for (size = 0; enviro[size]; size++)
		;

	new_enviro = malloc(sizeof(char *) * (size + 1));
	if (!new_enviro)
		return (NULL);

	for (index = 0; enviro[index]; index++)
	{
		new_enviro[index] = malloc(_strlen(enviro[index]) + 1);

		if (!new_enviro[index])
		{
			for (index--; index >= 0; index--)
				free(new_enviro[index]);
			free(new_enviro);
			return (NULL);
		}
		str_cpy(new_enviro[index], enviro[index]);
	}
	new_enviro[index] = NULL;

	return (new_enviro);
}

/**
 * free_env - Frees the environment copy.
 */
void free_env(void)
{
	int index;

	for (index = 0; enviro[index]; index++)
		free(enviro[index]);
	free(enviro);
}

/**
 * get_env - Gets an environmental variable.
 * @var: The name of the environmental variable.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **get_env(const char *var)
{
	int index, len;

	len = str_len(var);
	for (index = 0; enviro[index]; index++)
	{
		if (str_ncmp(var, enviro[index], len) == 0)
			return (&enviro[index]);
	}

	return (NULL);
}
