/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:04:22 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/29 17:58:46 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

int	redirect_in(t_data *data, int token_count)
{
	if (data->tokens[data->current_token].type == TOKEN_REDIRECT_IN)
	{
		if (data->current_token + 1 >= token_count)
		{
			printf("minishell: syntax error near unexpected token '<'\n");
			return (1);
		}
		data->current_token++;
		data->command->input_fd = open(data->tokens[data->current_token].value,
				O_RDONLY);
		if (data->command->input_fd == -1)
		{
			printf("minishell: %s: No such file or directory\n",
				data->tokens[data->current_token].value);
			return (1);
		}
		return (1);
	}
	return (0);
}

int	redirect_out(t_data *data, int token_count)
{
	if (data->tokens[data->current_token].type == TOKEN_REDIRECT_OUT)
	{
		if (data->current_token + 1 >= token_count)
		{
			printf("minishell: syntax error near unexpected token '>'\n");
			return (1);
		}
		(data->current_token)++;
		data->command->output_fd = open(data->tokens[data->current_token].value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->command->output_fd == -1)
		{
			printf("minishell: %s: Cannot create file\n",
				data->tokens[data->current_token].value);
			return (1);
		}
		return (1);
	}
	return (0);
}

int	handle_redirection(t_data *data)
{
	if (data->tokens[data->current_token].type == TOKEN_REDIRECT_IN)
	{
		if (redirect_in(data, data->token_count))
		{
			if (data->command->input_fd == -1)
				return (1);
		}
	}
	else if (data->tokens[data->current_token].type == TOKEN_REDIRECT_OUT)
	{
		if (redirect_out(data, data->token_count))
		{
			if (data->command->output_fd == -1)
				return (1);
		}
	}
	return (0);
}
