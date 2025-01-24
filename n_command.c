/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:08:12 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/24 18:04:16 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

int	process_command_line(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	data->pid_index = 0;
	data->pids = malloc(sizeof(pid_t) * (data->token_count + 1));
	while (i <= data->token_count)
	{
		data->pids[i] = -1;
		i++;
	}
	while (data->current_token < data->token_count)
	{
		if (parse_command(data) == 0)
		{
			if (execute_command(data) == 1)
				return (1);
		}
		if (data->current_token < data->token_count
			&& data->tokens[data->current_token].type == TOKEN_PIPE)
		{
			data->current_token++;
		}
	}
	i = 0;
	while (data->pids[i] != -1)
	{
		waitpid(data->pids[i], &status, 0);
		i++;
	}
	return (0);
}

int	parse_command(t_data *data)
{
	data->command = malloc(sizeof(t_command));
	data->command->args = malloc(sizeof(char *) * data->token_count);
	data->command->input_fd = STDIN_FILENO;
	data->command->output_fd = STDOUT_FILENO;
	data->command->fd_out = -1;
	data->command->fd_in = -1;
	data->command->args_count = 0;
	while (data->current_token < data->token_count)
	{
		if (if_pipe(data->tokens[data->current_token]))
			break ;
		else if (redirect_in(data, data->token_count))
		{
			if (data->command->input_fd == -1)
				return (1);
		}
		else if (redirect_out(data, data->token_count))
		{
			if (data->command->output_fd == -1)
				return (1);
		}
		else
			if_word(data);
		data->current_token++;
	}
	data->command->args[data->command->args_count] = NULL;
	if (data->command->args_count == 0)
		return (1);
	return (0);
}

int	execute_command(t_data *data)
{
	int		pipe_fd[2];
	char	*cmd_path;

	if (data->current_token < data->token_count
		&& data->tokens[data->current_token].type == TOKEN_PIPE)
	{
		pipe(pipe_fd);
		data->command->fd_in = pipe_fd[0];
		data->command->fd_out = pipe_fd[1];
	}
	cmd_path = find_command_path(data->command->args[0]);
	if (!cmd_path)
	{
		printf("%s: command not found\n", data->command->args[0]);
		return (1);
	}
	data->pid = fork();
	data->pids[data->pid_index] = data->pid;
	data->pid_index++;
	if (data->pid == 0)
	{
		close(data->command->fd_in);
		dup2(data->command->fd_out, STDOUT_FILENO);
		close(data->command->fd_out);
		execve(cmd_path, data->command->args, data->env);
		perror("execve failed");
		exit(1);
	}
	else
	{
		close(data->command->fd_out);
		data->command->fd_in = pipe_fd[0];
		close(data->command->fd_in);
	}
	return (0);
}
