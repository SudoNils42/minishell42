/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:04:22 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/31 16:37:23 by nbonnet          ###   ########.fr       */
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
			printf("minishell: syntax error near unexpected token '<'\n");
			return (-1);
		}
		filename = data->tokens[data->current_token + 1].value;
		data->command->input_fd = open(filename, O_RDONLY);
		if (data->command->input_fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", filename);
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
			printf("minishell: syntax error near unexpected token '>'\n");
			return (-1);
		}
		filename = data->tokens[data->current_token + 1].value;
		data->command->output_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->command->output_fd == -1)
		{
			printf("minishell: %s: Cannot create file\n", filename);
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
			printf("minishell: syntax error near unexpected token '>>'\n");
			return (-1);
		}
		filename = data->tokens[data->current_token + 1].value;
		data->command->output_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (data->command->output_fd == -1)
		{
			printf("minishell: %s: Cannot open file\n", filename);
			return (-1);
		}
		return (2);
	}
	return (0);
}

int	handle_redirection(t_data *data)
{
	int	processed;

	if ((processed = redirect_in(data, data->token_count)) != 0)
	{
		if (processed == -1)
			return (-1);
		data->current_token += processed;
		return (processed);
	}
	if ((processed = redirect_out(data, data->token_count)) != 0)
	{
		if (processed == -1)
			return (-1);
		data->current_token += processed;
		return (processed);
	}
	if ((processed = redirect_append(data, data->token_count)) != 0)
	{
		if (processed == -1)
			return (-1);
		data->current_token += processed;
		return (processed);
	}
	return (0);
}
