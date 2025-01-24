/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_pipe_or_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:10:20 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/23 12:31:30 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

int	if_pipe(t_token token)
{
	if (token.type == TOKEN_PIPE)
		return (1);
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
