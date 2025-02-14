/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sub_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:22:09 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/14 23:57:36 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_words(t_data *data, int *i)
{
	int		sub_token_count;
	char	quote_type;

	while (data->content[*(i)])
	{
		if (data->content[*(i)] == '\'' || data->content[*(i)] == '"')
		{
			quote_type = data->content[(*i)++];
			while (data->content[(*i)] && data->content[(*i)] != quote_type)
				(*i)++;
			if (data->content[(*i)] == quote_type)
				(*i)++;
			sub_token_count++;
		}
		else
			while (data->content[(*i)] && data->content[(*i)] != '\''
				&& data->content[(*i)] != '"' && data->content[(*i)] != ' '
				&& data->content[(*i)] != '|' && data->content[(*i)] != '<'
				&& data->content[(*i)] != '>')
				(*i)++;
		sub_token_count++;
	}
	return (sub_token_count);
}

int	number_of_sub_token(t_data *data, int i)
{
	int	sub_token_count;

	sub_token_count = 0;
	sub_token_count = find_words(data, &i);
	return (sub_token_count);
}

void	sub_token_quotes(t_token *token, t_data *data, int *i,
		int *sub_token_count)
{
	int		start;
	char	quote_type;

	quote_type = data->content[(*i)++];
	start = *i;
	while (data->content[*i] && data->content[*i] != quote_type)
		(*i)++;
	token->sub_tokens[*sub_token_count] = malloc(sizeof(t_sub_token));
	if (!token->sub_tokens[*sub_token_count])
		return ;
	if (quote_type == '\'')
		token->sub_tokens[*sub_token_count]->type = TOKEN_SQUOTE;
	else if (quote_type == '"')
		token->sub_tokens[*sub_token_count]->type = TOKEN_DQUOTE;
	token->sub_tokens[*sub_token_count]->content = ft_substr(data->content,
			start, *i - start);
	if (quote_type == '"')
	{
		token->sub_tokens[*sub_token_count]->content
			= manage_dollar(token->sub_tokens[*sub_token_count]->content,
				data);
	}
	(*sub_token_count)++;
	if (data->content[*i] == quote_type)
		(*i)++;
}

void	sub_token_word(t_token *token, t_data *data, int *i,
		int *sub_token_count)
{
	int	start;

	start = *i;
	while (data->content[*i] && data->content[*i] != '\''
		&& data->content[*i] != '"' && data->content[*i] != ' '
		&& data->content[*i] != '|' && data->content[*i] != '<'
		&& data->content[*i] != '>')
		(*i)++;
	if (*i > start)
	{
		token->sub_tokens[*sub_token_count] = malloc(sizeof(t_sub_token));
		if (!token->sub_tokens[*sub_token_count])
			return ;
		token->sub_tokens[*sub_token_count]->type = TOKEN_NO_QUOTE;
		token->sub_tokens[*sub_token_count]->content = ft_substr(data->content,
				start, *i - start);
		token->sub_tokens[*sub_token_count]->content
			= manage_dollar(token->sub_tokens[*sub_token_count]->content,
				data);
		(*sub_token_count)++;
	}
}

void	analyse_quotes(t_token *token, t_data *data)
{
	int	sub_token_count;
	int	i;

	i = 0;
	sub_token_count = number_of_sub_token(data, i);
	token->sub_tokens = malloc(sizeof(t_sub_token *) * (sub_token_count + 1));
	if (!token->sub_tokens)
		return ;
	token->sub_tokens[sub_token_count] = NULL;
	sub_token_count = 0;
	while (data->content[i])
	{
		if (data->content[i] == '\'' || data->content[i] == '"')
			sub_token_quotes(token, data, &i, &sub_token_count);
		else
			sub_token_word(token, data, &i, &sub_token_count);
	}
}
