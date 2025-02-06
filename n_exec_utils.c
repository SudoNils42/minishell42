/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_exec_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:51:27 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/06 16:10:29 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (data->pids[i] != -1)
		waitpid(data->pids[i++], &status, 0);
}

void	run_child_process(t_data *data, char *cmd_path, int is_builtin)
{
	if (data->command->input_fd != STDIN_FILENO)
		dup2(data->command->input_fd, STDIN_FILENO);
	if (data->command->output_fd != STDOUT_FILENO)
		dup2(data->command->output_fd, STDOUT_FILENO);
	else if (data->command->fd_out != -1)
		dup2(data->command->fd_out, STDOUT_FILENO);
	if (data->prev_pipe_read_end != -1)
		close(data->prev_pipe_read_end);
	if (is_builtin)
		exec_builtins(data);
	else
	{
		execve(cmd_path, data->command->args, data->env);
		perror("execve failed");
	}
	exit(1);
}

void	cleanup_parent(t_data *data)
{
	if (data->command->fd_out != -1)
		close(data->command->fd_out);
	if (data->command->input_fd != STDIN_FILENO)
		close(data->command->input_fd);
	if (data->command->output_fd != STDOUT_FILENO)
		close(data->command->output_fd);
}

void	setup_pipe(t_data *data, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	data->command->fd_out = pipe_fd[1];
	data->prev_pipe_read_end = pipe_fd[0];
}

void	prepare_pipe_connection(t_data *data)
{
	int	pipe_fd[2];

	if (data->current_token < data->token_count
		&& data->tokens[data->current_token].type == TOKEN_PIPE
		&& data->command->output_fd == STDOUT_FILENO)
		setup_pipe(data, pipe_fd);
	else
		data->command->fd_out = -1;
}
