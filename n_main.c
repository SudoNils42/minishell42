#include "n_minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	pid_t	pid;
	char	*path;
	char	*full_path;
	char	*args[100];
	char	*dir;
	int		i;

	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		add_history(input);
		args[0] = ft_strtok(input, " ");
		i = 1;
		while ((args[i -1] != NULL) && (i < 100))
		{
			args[i] = ft_strtok(NULL, " ");
			i++;
		}
		pid = fork();
		if (pid == 0)
		{
			path = getenv("PATH");
			dir = ft_strtok(path, ":");
			while (dir != NULL)
			{
				full_path = ft_strjoin_with_slash(dir, args[0]);
				if (access(full_path, X_OK) == 0)
				{
					execve(full_path, args, env);
					break ;
				}
				dir = ft_strtok(NULL, ":");
			}
			printf("%s: command not found\n", *args);
			exit(1);
		}
		else if (pid > 0)
			wait(NULL);
		free(input);
	}
	return (0);
}
