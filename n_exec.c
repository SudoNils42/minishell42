/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:56:58 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/13 16:41:09 by nbonnet          ###   ########.fr       */
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

void	handle_previous_pipe(t_data *data)
{
	if (data->prev_pipe_read_end == -1)
		return ;
	if (data->command->input_fd == STDIN_FILENO)
	{
		data->command->input_fd = data->prev_pipe_read_end;
		data->prev_pipe_read_end = -1;
	}
	else
	{
		close(data->prev_pipe_read_end);
		data->prev_pipe_read_end = -1;
	}
}

int	parse_command(t_data *data)
{
	int	redirect_processed;

	init_command(data);
	handle_previous_pipe(data);
	while (data->current_token < data->token_count)
	{
		if (data->tokens[data->current_token].type == TOKEN_PIPE)
			break ;
		redirect_processed = handle_redirection(data);
		if (redirect_processed == -1)
			return (1);
		if (redirect_processed > 0)
		{
			if ((data->command->input_fd == -1) || (data->command->output_fd ==
					-1))
				return (1);
		}
		else if (redirect_processed == 0)
		{
			data->command->args[data->command->args_count] = data->tokens[data->current_token].value;
			data->command->args_count++;
			data->current_token++;
		}
	}
	data->command->args[data->command->args_count] = NULL;
	return (data->command->args_count == 0);
}

int	execute_command(t_data *data)
{
	char	*cmd_path;
	int		is_builtin_cmd;

	prepare_pipe_connection(data);
	is_builtin_cmd = is_builtin(data);
	if (is_builtin_cmd && data->command->input_fd == STDIN_FILENO
		&& data->command->output_fd == STDOUT_FILENO && data->command->fd_out ==
		-1 && data->prev_pipe_read_end == -1)
	{
		exec_builtins(data);
		return (0);
	}
	if (is_builtin_cmd)
		cmd_path = NULL;
	else
	{
		cmd_path = find_command_path(data->command->args[0], data);
		if (!cmd_path)
		{
			ft_putstr_fd(data->command->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			return (1);
		}
	}
	data->pid = fork();
	data->pids[data->pid_index++] = data->pid;
	if (data->pid == 0)
		run_child_process(data, cmd_path, is_builtin_cmd);
	else
		cleanup_parent(data);
	return (0);
}

int	is_builtin(t_data *data)
{
	char	*cmd;

	if (!data->command->args[0])
		return (0);
	cmd = data->command->args[0];
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
