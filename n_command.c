/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:08:12 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/22 19:24:29 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

int	process_command_line(t_data *data)
{
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
	return (0);
}

int	parse_command(t_data *data)
{
	data->command = malloc(sizeof(t_command));
	data->command->args = malloc(sizeof(char *) * data->token_count);
	data->command->input_fd = STDIN_FILENO;
	data->command->output_fd = STDOUT_FILENO;
	data->command->pipe_read = data->next_pipe_read;
	data->command->pipe_write = -1;
	data->next_pipe_read = -1;
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
		data->command->pipe_write = pipe_fd[1];
		data->next_pipe_read = pipe_fd[0];
	}
	cmd_path = find_command_path(data->command->args[0]);
	if (!cmd_path)
	{
		printf("%s: command not found\n", data->command->args[0]);
		return (1);
	}
	data->pid = fork();
	if (data->pid == 0)
	{
		handle_fd(data);
		execve(cmd_path, data->command->args, data->env);
		perror("execve failed");
		exit(1);
	}
	else
	{
		if (data->command->pipe_read != -1)
			close(data->command->pipe_read);
		if (data->command->pipe_write != -1)
			close(data->command->pipe_write);
		// waitpid(data->pid, NULL, 0); fd 0 problem
	}
	return (0);
}
