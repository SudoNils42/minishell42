/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:48:12 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/23 12:31:32 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

t_token	*tokenize_input(t_data *data)
{
	char	**raw_tokens;
	t_token	*tokens;
	int		i;

	data->token_count = 0;
	raw_tokens = ft_split(data->input, ' ');
	if (!raw_tokens)
		return (NULL);
	i = 0;
	while (raw_tokens[i] != NULL)
	{
		data->token_count++;
		i++;
	}
	tokens = malloc(sizeof(t_token) * data->token_count);
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < data->token_count)
	{
		tokens[i].value = ft_strdup(raw_tokens[i]);
		tokens[i].type = get_token_type(raw_tokens[i]);
		i++;
	}
	return (tokens);
}


int	get_token_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(token, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	if (ft_strcmp(token, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	else
		return (TOKEN_WORD);
}
