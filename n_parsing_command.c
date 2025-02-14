/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_parsing_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:14:53 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/14 22:15:59 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	manage_redirect_processed(t_data *data)
{
	int	redirect_processed;

	while (data->current_token < data->token_count)
	{
		if (data->tokens[data->current_token].type == TOKEN_PIPE)
			break ;
		redirect_processed = handle_redirection(data);
		if (redirect_processed == -1)
			return (1);
		if (redirect_processed > 0)
		{
			if ((data->command->input_fd == -1)
				|| (data->command->output_fd == -1))
				return (1);
		}
		else if (redirect_processed == 0)
		{
			data->command->args[data->command->args_count]
				= data->tokens[data->current_token].value;
			data->command->args_count++;
			data->current_token++;
		}
	}
	return (0);
}

int	parse_command(t_data *data)
{
	int	return_value;

	init_command(data);
	handle_previous_pipe(data);
	return_value = manage_redirect_processed(data);
	if (return_value == 1)
		return (1);
	data->command->args[data->command->args_count] = NULL;
	if (data->command->args_count == 0)
		return (1);
	return (0);
}
