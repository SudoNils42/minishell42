/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:10:21 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/12 19:47:24 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char **env)
{
	data->env = env;
	data->tokens = NULL;
	data->token_count = 0;
	data->current_token = 0;
	data->command = NULL;
	data->input = NULL;
	data->pids = NULL;
	data->pid_index = 0;
	data->exit_status = 0;
	data->flag_error = 0;
	data->start = 0;
}

void	init_command(t_data *data)
{
	data->command = malloc(sizeof(t_command));
	data->command->args = malloc(sizeof(char *) * (data->token_count + 1));
	data->command->fd_out = -1;
	data->command->fd_in = -1;
	data->command->error_pipe_read = -1;
	data->command->error_pipe_write = -1;
	data->command->args_count = 0;
	data->command->input_fd = STDIN_FILENO;
	data->command->output_fd = STDOUT_FILENO;
	data->command->args[0] = NULL;
}

void	init_pid_list(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->token_count)
		data->pids[i++] = -1;
}
