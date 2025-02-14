/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:24:57 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/15 00:52:24 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_data *data, char *start, int len, int type)
{
	t_token	new_token;
	t_token	*new_tokens;
	int		i;

	new_token.value = ft_strndup(start, len);
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

void	handle_operator(t_data *data, int *i)
{
	int	op_len;
	int	type;

	op_len = 1;
	type = TOKEN_WORD;
	if ((data->input[*i] == '>' && data->input[*i + 1] == '>')
		|| (data->input[*i] == '<' && data->input[*i + 1] == '<'))
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

void	find_end_of_word(t_data *data, int *i)
{
	char	quote_type;

	while (data->input[*i] && data->input[*i] != ' ' && data->input[*i] != '|'
		&& data->input[*i] != '<' && data->input[*i] != '>')
	{
		if (data->input[*i] == '\'' || data->input[*i] == '"')
		{
			quote_type = data->input[*i];
			(*i)++;
			while (data->input[*i] && data->input[*i] != quote_type)
				(*i)++;
			if (data->input[*i] != quote_type)
			{
				ft_putstr_fd("minishell: unclosed quote\n", 2);
				data->exit_status = 1;
				return ;
			}
			(*i)++;
		}
		else
			(*i)++;
	}
}

void	parse_word(t_data *data, int *i)
{
	t_token	token;
	char	*tmp;
	char	*new_tmp;
	int		start;
	int		j;

	start = *i;
	find_end_of_word(data, i);
	data->content = ft_substr(data->input, start, *i - start);
	token.value = data->content;
	token.type = TOKEN_WORD;
	token.sub_tokens = NULL;
	analyse_quotes(&token, data);
	tmp = ft_strdup("");
	j = 0;
	while (token.sub_tokens && token.sub_tokens[j])
	{
		new_tmp = ft_strjoin(tmp, token.sub_tokens[j]->content);
		tmp = new_tmp;
		j++;
	}
	token.value = tmp;
	add_token(data, token.value, ft_strlen(token.value), TOKEN_WORD);
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
		else if (data->input[i] == '|' || data->input[i] == '<'
			|| data->input[i] == '>')
			handle_operator(data, &i);
		else
			parse_word(data, &i);
	}
}
