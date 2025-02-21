/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:04:22 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/21 15:17:59 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in(t_data *data, int token_count)
{
	char	*filename;

	if (data->tokens[data->current_token].type == TOKEN_REDIRECT_IN)
	{
		if (data->current_token + 1 >= token_count)
		{
			ft_putstr_fd(ERROR, 2);
			return (-1);
		}
		filename = data->tokens[data->current_token + 1].value;
		data->command->input_fd = open(filename, O_RDONLY);
		if (data->command->input_fd == -1)
		{
			data->exit_status = 1;
			print_error(filename);
			return (-1);
		}
		return (2);
	}
	return (0);
}

int	redirect_out(t_data *data, int token_count)
{
	char	*filename;

	if (data->tokens[data->current_token].type == TOKEN_REDIRECT_OUT)
	{
		if (data->current_token + 1 >= token_count)
		{
			ft_putstr_fd(ERROR, 2);
			return (-1);
		}
		filename = data->tokens[data->current_token + 1].value;
		data->command->output_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->command->output_fd == -1)
		{
			data->exit_status = 1;
			print_error(filename);
			return (-1);
		}
		return (2);
	}
	return (0);
}

int	redirect_append(t_data *data, int token_count)
{
	char	*filename;

	if (data->tokens[data->current_token].type == TOKEN_REDIRECT_APPEND)
	{
		if (data->current_token + 1 >= token_count)
		{
			ft_putstr_fd(ERROR, 2);
			return (-1);
		}
		filename = data->tokens[data->current_token + 1].value;
		data->command->output_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (data->command->output_fd == -1)
		{
			data->exit_status = 1;
			print_error(filename);
			return (-1);
		}
		return (2);
	}
	return (0);
}

int	redirect_heredoc(t_data *data, int token_count)
{
	char	*delimiter;
	int		pipe_fd[2];

	if (data->tokens[data->current_token].type != TOKEN_HEREDOC)
		return (0);
	if (data->current_token + 1 >= token_count)
	{
		ft_putstr_fd(ERROR, 2);
		return (-1);
	}
	delimiter = data->tokens[data->current_token + 1].value;
	pipe(pipe_fd);
	inside_heredoc(delimiter, pipe_fd);
	data->command->input_fd = pipe_fd[0];
	return (2);
}

int	handle_redirection(t_data *data)
{
	int	processed;

	processed = redirect_in(data, data->token_count);
	if (processed != 0)
		return (process_redirection(processed, data));
	processed = redirect_out(data, data->token_count);
	if (processed != 0)
		return (process_redirection(processed, data));
	processed = redirect_append(data, data->token_count);
	if (processed != 0)
		return (process_redirection(processed, data));
	processed = redirect_heredoc(data, data->token_count);
	if (processed != 0)
		return (process_redirection(processed, data));
	return (0);
}
