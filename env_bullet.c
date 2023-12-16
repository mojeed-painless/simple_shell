#include "shell.h"

int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shell_env - Prints the current environ.
 * @args: An array of arguments passed.
 * @front: A double pointer.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int shell_env(char **args, char __attribute__((__unused__)) **front)
{
	int index;
	char n_c = '\n';

	if (!enviro)
		return (-1);

	for (index = 0; enviro[index]; index++)
	{
		write(STDOUT_FILENO, enviro[index], str_len(enviro[index]));
		write(STDOUT_FILENO, &n_c, 1);
	}

	(void)args;
	return (0);
}

/**
 * shell_setenv - Changes or adds an environmental variable.
 * @args: An array of arguments passed.
 * @front: A double pointer.
 * Description: args[1] is the name.
 *              args[2] is the value.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_enviro, *new_val;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_val = malloc(str_len(args[0]) + 1 + str_len(args[1]) + 1);
	if (!new_val)
		return (create_error(args, -1));
	str_cpy(new_val, args[0]);
	str_cat(new_val, "=");
	str_cat(new_val, args[1]);

	env_var = get_env(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;
		return (0);
	}
	for (size = 0; enviro[size]; size++)
		;

	new_enviro = malloc(sizeof(char *) * (size + 2));
	if (!new_enviro)
	{
		free(new_val);
		return (create_error(args, -1));
	}

	for (index = 0; enviro[index]; index++)
		new_enviro[index] = enviro[index];

	free(enviro);
	enviro = new_enviro;
	enviro[index] = new_val;
	enviro[index + 1] = NULL;

	return (0);
}

/**
 * shell_unsetenv - Deletes an environmental variable.
 * @args: An array of arguments passed.
 * @front: A double pointer.
 * Description: args[1] is the PATH variabl.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_enviro;
	size_t size;
	int index1, index2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = get_env(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; enviro[size]; size++)
		;

	new_enviro = malloc(sizeof(char *) * size);
	if (!new_enviro)
		return (create_error(args, -1));

	for (index1 = 0, index2 = 0; enviro[index]; index++)
	{
		if (*env_var == enviro[index])
		{
			free(*env_var);
			continue;
		}
		new_enviro[index2] = enviro[index];
		index2++;
	}
	free(enviro);
	enviro = new_enviro;
	enviro[size - 1] = NULL;

	return (0);
}
