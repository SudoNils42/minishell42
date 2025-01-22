/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_if_token_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:10:20 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/22 17:39:27 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

int	if_pipe(t_token token)
{
	if (token.type == TOKEN_PIPE)
		return (1);
	return (0);
}

int	if_redirect_in(t_data *data, int token_count)
{
	if (data->tokens[data->current_token].type == TOKEN_REDIRECT_IN)
	{
		if (data->current_token + 1 >= token_count)
		{
			printf("minishell: syntax error near unexpected token '<'\n");
			return (1);
		}
		(data->current_token)++;
		data->command->input_fd = open(data->tokens[data->current_token].value, O_RDONLY);
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

int	if_redirect_out(t_data *data, int token_count)
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

int	if_word(t_data *data)
{
	if (data->tokens[data->current_token].type == TOKEN_WORD)
	{
		data->command->args[data->command->args_count] = ft_strdup(data->tokens[data->current_token].value);
		data->command->args_count++;
	}
	return (0);
}
