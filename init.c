/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:10:21 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/21 17:21:00 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->env = NULL;
	data->exp = NULL;
	data->raw_tokens = NULL;
	data->input = NULL;
	data->content = NULL;
	data->token_count = 0;
	data->start = 0;
	data->flag_error = 0;
	data->current_token = 0;
	data->total_pipes = 0;
	data->prev_pipe_read_end = -1;
	data->pid = 0;
	data->pids = NULL;
	data->pid_index = 0;
	data->exit_status = 0;
	data->command = NULL;
	data->tokens = NULL;
}

void	init_command(t_data *data)
{
	if (data->command) // Libérer l'ancienne commande si elle existe
	{
		free_command(data->command);
		free(data->command);
	}
	data->command = malloc(sizeof(t_command));
	if (!data->command)
		return ;
	data->command->args = malloc(sizeof(char *) * (data->token_count + 1));
	if (!data->command->args)
	{
		free(data->command);
		return ;
	}
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
