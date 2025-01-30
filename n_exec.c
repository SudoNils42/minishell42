/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:08:12 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/30 16:49:38 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_command_line(t_data *data)
{
	data->pid_index = 0;
	data->pids = malloc(sizeof(pid_t) * (data->token_count + 1));
	init_pid_list(data);
	while (data->current_token < data->token_count)
	{
		if (parse_command(data) == 0 && execute_command(data) == 1)
			return (1);
		if (data->current_token < data->token_count
			&& data->tokens[data->current_token].type == TOKEN_PIPE)
			data->current_token++;
	}
	wait_for_children(data);
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
	init_command(data);
	handle_previous_pipe(data);
	while (data->current_token < data->token_count)
	{
		if (data->tokens[data->current_token].type == TOKEN_PIPE)
			break ;
		else if (handle_redirection(data) == 1)
		{
			if ((data->command->input_fd == -1) || (data->command->output_fd ==
					-1))
				return (1);
		}
		else
		{
			data->command->args[data->command->args_count] = data->tokens[data->current_token].value;
			data->command->args_count++;
		}
		data->current_token++;
	}
	data->command->args[data->command->args_count] = NULL;
	return (data->command->args_count == 0);
}

int	execute_command(t_data *data)
{
	char	*cmd_path;

	prepare_pipe_connection(data);
	// Nouvelle vérification des builtins AVANT le fork
	if (is_builtin(data))
	{
		exec_builtins(data); // Exécuté dans le processus principal
		return (0);
	}
	cmd_path = find_command_path(data->command->args[0]);
	if (!cmd_path)
		return (printf("%s: command not found\n", data->command->args[0]), 1);
	data->pid = fork();
	data->pids[data->pid_index++] = data->pid;
	if (data->pid == 0)
		run_child_process(data, cmd_path);
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
