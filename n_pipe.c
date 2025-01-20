/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:26:10 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/20 22:49:36 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

void	execute_cmd_arg(t_data *data)
{
	int	i;

	data->pid = fork();
	if (data->pid == 0)
	{
		check_redirect_input(data);
		if (data->fd_input != 0)
		{
			dup2(data->fd_input, 0);
			close(data->fd_input);
		}
		if (data->fd[1] != 1)
		{
			dup2(data->fd[1], 1);
			close(data->fd[1]);
		}
		data->path = getenv("PATH");
		data->dir = ft_split(data->path, ':');
		i = 0;
		while (data->dir[i] != NULL)
		{
			data->full_path = ft_strjoin_with_slash(data->dir[i],
					data->cmd_arg_pipe[data->cmd_index][0]);
			if (access(data->full_path, X_OK) == 0)
			{
				if (data->flag_redirect == 1)
				{
					execve(data->full_path, data->cmd_arg_pipe[data->cmd_index + 1],
						data->env);
					exit(1);
				}
				else
				{
					execve(data->full_path, data->cmd_arg_pipe[data->cmd_index],
						data->env);
					exit(1);
				}
			}
			i++;
		}
		printf("%s: command not found\n", data->cmd_arg_pipe[data->cmd_index][0]);
		exit(1);
	}
}

void	create_pipe(t_data *data)
{
	data->fd_input = 0;
	data->cmd_index = 0;
	while (data->cmd_index < data->cmd_arg_count)
	{
		if (data->cmd_index == data->cmd_arg_count - 1)
			data->fd[1] = 1;
		else
			pipe(data->fd);
		execute_cmd_arg(data);
		if (data->fd_input != 0)
			close(data->fd_input);
		if (data->cmd_index < data->cmd_arg_count - 1)
			close(data->fd[1]);
		data->fd_input = data->fd[0];
		data->cmd_index++;
	}
	while (wait(NULL) > 0)
		;
}

void	split_cmd_arg_pipe(t_data *data)
{
	int	i;

	i = 0;
	data->cmd_arg = ft_split(data->input_cpy, '|');
	data->cmd_arg_count = 0;
	while (data->cmd_arg[data->cmd_arg_count] != NULL)
		data->cmd_arg_count++;
	data->cmd_arg_pipe = malloc(sizeof(char **) * (data->cmd_arg_count + 1));
	while (i < data->cmd_arg_count)
	{
		data->cmd_arg_pipe[i] = ft_split(data->cmd_arg[i], ' ');
		i++;
	}
	data->cmd_arg_pipe[i] = NULL;
}

void	start_pipe(t_data *data)
{
	data->input_cpy = malloc(strlen(data->input) + 1);
	ft_strcpy(data->input_cpy, data->input);
	split_cmd_arg_pipe(data);
	create_pipe(data);
}
