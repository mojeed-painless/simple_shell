#include "shell.h"

int (*get_builtin(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - Matches a command with a corresponding.
 * @command: The command.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shell_exit },
		{ "env", shell_env },
		{ "setenv", shell_setenv },
		{ "unsetenv", shell_unsetenv },
		{ "cd", shell_cd },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int a;

	for (a = 0; funcs[a].name; a++)
	{
		if (str_cmp(funcs[a].name, command) == 0)
			break;
	}
	return (funcs[a].funct);
}

/**
 * shell_exit - Causes normal process termination.
 * @args: An array of arguments.
 * @front: A double pointer.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 */
int shell_exit(char **args, char **front)
{
	int a, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			a = 1;
			len_of_int++;
		}
		for (; args[0][a]; a++)
		{
			if (a <= len_of_int && args[0][a] >= '0' && args[0][a] <= '9')
				num = (num * 10) + (args[0][a] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

/**
 * shell_cd - Changes the current directory.
 * @args: An array of arguments.
 * @front: A double pointer.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **direct_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat direct;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || str_cmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (get_env("OLDPWD") != NULL)
					(chdirect(*get_env("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &direct) == 0 && S_ISDIR(direct.st_mode)
					&& ((direct.st_mode & S_IXUSR) != 0))
				chdirect(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (get_env("HOME") != NULL)
			chdirect(*(get_env("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	direct_info = malloc(sizeof(char *) * 2);
	if (!direct_info)
		return (-1);

	direct_info[0] = "OLDPWD";
	direct_info[1] = oldpwd;
	if (shell_setenv(direct_info, direct_info) == -1)
		return (-1);

	direct_info[0] = "PWD";
	direct_info[1] = pwd;
	if (shell_setenv(direct_info, direct_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, str_len(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(direct_info);
	return (0);
}

/**
 * shell_help - Displays information.
 * @args: An array of arguments.
 * @front: A pointer
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (str_cmp(args[0], "alias") == 0)
		help_alias();
	else if (str_cmp(args[0], "cd") == 0)
		help_cd();
	else if (str_cmp(args[0], "exit") == 0)
		help_exit();
	else if (str_cmp(args[0], "env") == 0)
		help_env();
	else if (str_cmp(args[0], "setenv") == 0)
		help_setenv();
	else if (str_cmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (str_cmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, str_len(name));

	return (0);
}
