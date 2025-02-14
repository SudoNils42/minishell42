/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:56:58 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/14 22:24:16 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_command_line(t_data *data)
{
	g_signals(1);
	data->pid_index = 0;
	data->pids = malloc(sizeof(pid_t) * (data->token_count + 1));
	init_pid_list(data);
	while (data->current_token < data->token_count)
	{
		if (parse_command(data) != 0)
		{
			while (data->current_token < data->token_count
				&& data->tokens[data->current_token].type != TOKEN_PIPE)
				data->current_token++;
			if (data->current_token < data->token_count
				&& data->tokens[data->current_token].type == TOKEN_PIPE)
				data->current_token++;
			continue ;
		}
		if (execute_command(data) != 0)
			return (1);
		if (data->current_token < data->token_count
			&& data->tokens[data->current_token].type == TOKEN_PIPE)
			data->current_token++;
	}
	wait_for_children(data);
	g_signals(0);
	return (0);
}

void	start_fork(t_data *data, char *cmd_path, int is_builtin_cmd)
{
	data->pid = fork();
	data->pids[data->pid_index++] = data->pid;
	if (data->pid == 0)
		run_child_process(data, cmd_path, is_builtin_cmd);
	else
		cleanup_parent(data);
}

int	execute_command(t_data *data)
{
	char	*cmd_path;
	int		is_builtin_cmd;

	prepare_pipe_connection(data);
	is_builtin_cmd = is_builtin(data);
	if (is_builtin_cmd && data->command->input_fd == STDIN_FILENO
		&& data->command->output_fd == STDOUT_FILENO
		&& data->command->fd_out == -1 && data->prev_pipe_read_end == -1)
	{
		exec_builtins(data);
		return (0);
	}
	cmd_path = NULL;
	if (is_builtin_cmd == 0)
	{
		cmd_path = find_command_path(data->command->args[0], data);
		if (!cmd_path)
		{
			ft_putstr_fd(data->command->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			return (1);
		}
	}
	start_fork(data, cmd_path, is_builtin_cmd);
	return (0);
}
