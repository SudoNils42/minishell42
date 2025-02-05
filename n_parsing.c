/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:24:57 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/06 00:41:52 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_two_char_op(char c1, char c2)
{
	return ((c1 == '>' && c2 == '>') || (c1 == '<' && c2 == '<'));
}

void	add_token(t_data *data, char *start, int len, int type)
{
	t_token	new_token;
	t_token	*new_tokens;
	int		i;
	char	*expanded;

	new_token.value = ft_strndup(start, len);
	if (type != TOKEN_SQUOTE)
	{
		expanded = expand_variables(new_token.value, data);
		free(new_token.value);
		new_token.value = expanded;
	}
	new_token.type = type;
	new_tokens = malloc(sizeof(t_token) * (data->token_count + 1));
	i = -1;
	while (++i < data->token_count)
		new_tokens[i] = data->tokens[i];
	new_tokens[data->token_count] = new_token;
	data->token_count++;
	free(data->tokens);
	data->tokens = new_tokens;
}

void	handle_quotes(t_data *data, int *i, char quote_type)
{
	int	start;
	int	type;

	start = *i + 1;
	(*i)++;
	while (data->input[*i] && data->input[*i] != quote_type)
		(*i)++;
	if (!data->input[*i])
	{
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		data->exit_status = 1;
		return ;
	}
	if (quote_type == '\'')
		type = TOKEN_SQUOTE;
	else
		type = TOKEN_DQUOTE;
	add_token(data, data->input + start, *i - start, type);
	(*i)++;
}

void	handle_operator(t_data *data, int *i)
{
	int	op_len;
	int	type;

	op_len = 1;
	type = TOKEN_WORD;
	if (is_two_char_op(data->input[*i], data->input[*i + 1]))
	{
		op_len = 2;
		if (data->input[*i] == '>')
			type = TOKEN_REDIRECT_APPEND;
		else
			type = TOKEN_HEREDOC;
	}
	else if (data->input[*i] == '>')
		type = TOKEN_REDIRECT_OUT;
	else if (data->input[*i] == '<')
		type = TOKEN_REDIRECT_IN;
	else if (data->input[*i] == '|')
		type = TOKEN_PIPE;
	add_token(data, &data->input[*i], op_len, type);
	*i += op_len;
}

void	parse_word(t_data *data, int *i)
{
	int	start;

	start = *i;
	while (data->input[*i] && !ft_isspace(data->input[*i])
		&& !is_operator(data->input[*i]))
	{
		if (data->input[*i] == '\'' || data->input[*i] == '"')
			break ;
		(*i)++;
	}
	add_token(data, &data->input[start], *i - start, TOKEN_WORD);
}

void	parsing(t_data *data)
{
	int	i;

	i = 0;
	data->tokens = NULL;
	data->token_count = 0;
	while (data->input[i])
	{
		while (ft_isspace(data->input[i]))
			i++;
		if (!data->input[i])
			break ;
		if (data->input[i] == '\'' || data->input[i] == '"')
			handle_quotes(data, &i, data->input[i]);
		else if (is_operator(data->input[i]))
			handle_operator(data, &i);
		else
			parse_word(data, &i);
	}
}
