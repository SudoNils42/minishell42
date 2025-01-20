#include "n_minishell.h"

void	check_redirect_input(t_data *data)
{
	int	i;

	i = 0;
	data->flag_redirect = 0;
	data->new_fd_input = -1;
	while (data->cmd_arg_pipe[data->cmd_index][i] != NULL)
	{
		if (ft_strcmp(data->cmd_arg_pipe[data->cmd_index][i], "<") == 0)
		{
			if (data->cmd_arg_pipe[data->cmd_index][i + 1] == NULL)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				exit(1);
			}
			data->flag_redirect = 1;
			data->new_fd_input = open(data->cmd_arg_pipe[data->cmd_index][i
					+ 1], O_RDONLY);
			if (data->new_fd_input == -1)
			{
				printf("minishell: %s: No such file or directory\n",
					data->cmd_arg_pipe[data->cmd_index][i + 1]);
				exit(1);
			}
			if (dup2(data->new_fd_input, STDIN_FILENO) == -1)
			{
				perror("minishell");
				exit(1);
			}
			close(data->new_fd_input);
		}
		i++;
	}
}
