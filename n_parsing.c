/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:24:57 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/13 12:52:47 by nbonnet          ###   ########.fr       */
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

void	analyse_quotes(char *content, t_token *token, t_data *data)
{
	int			i;
	int			count;
	int			k;
	int			start;
	char		quote_type;
	t_sub_token	*sub;

	count = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '"')
		{
			quote_type = content[i++];
			while (content[i] && content[i] != quote_type)
				i++;
			if (content[i] == quote_type)
				i++;
			count++;
		}
		else
		{
			start = i;
			while (content[i] && content[i] != '\'' && content[i] != '"'
				&& content[i] != ' ' && content[i] != '|' && content[i] != '<'
				&& content[i] != '>')
				i++;
			if (i > start)
				count++;
		}
	}
	token->sub_token = malloc(sizeof(t_sub_token *) * (count + 1));
	if (!token->sub_token)
		return ;
	token->sub_token[count] = NULL;
	i = 0;
	k = 0;
	while (content[i] && k < count)
	{
		if (content[i] == '\'')
		{
			sub = malloc(sizeof(t_sub_token));
			if (!sub)
				return ;
			sub->type = TOKEN_SQUOTE;
			i++;
			start = i;
			while (content[i] && content[i] != '\'')
				i++;
			sub->content = ft_substr(content, start, i - start);
			if (content[i] == '\'')
				i++;
			token->sub_token[k++] = sub;
		}
		else if (content[i] == '"')
		{
			sub = malloc(sizeof(t_sub_token));
			if (!sub)
				return ;
			sub->type = TOKEN_DQUOTE;
			i++;
			start = i;
			while (content[i] && content[i] != '"')
				i++;
			sub->content = ft_substr(content, start, i - start);
			sub->content = expand_variables(sub->content, data);
			if (content[i] == '"')
				i++;
			token->sub_token[k++] = sub;
		}
		else
		{
			start = i;
			while (content[i] && content[i] != '\'' && content[i] != '"'
				&& content[i] != ' ' && content[i] != '|' && content[i] != '<'
				&& content[i] != '>')
				i++;
			if (i > start)
			{
				sub = malloc(sizeof(t_sub_token));
				if (!sub)
					return ;
				sub->type = TOKEN_NO_QUOTE;
				sub->content = ft_substr(content, start, i - start);
				sub->content = expand_variables(sub->content, data);
				token->sub_token[k++] = sub;
			}
		}
	}
}

void	parse_word(t_data *data, int *i)
{
	t_token	*token;
	int		start;
	char	*content;
	char	quote_type;
	int		j;
	char	*tmp;
	char	*new_tmp;

	start = *i;
	token = malloc(sizeof(t_token));
	if (!token)
		return ;
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
				free(token);
				return ;
			}
			(*i)++;
		}
		else
			(*i)++;
	}
	content = ft_substr(data->input, start, *i - start);
	token->value = content;
	token->type = TOKEN_WORD;
	token->sub_token = NULL;
	analyse_quotes(content, token, data);
	tmp = ft_strdup("");
	j = 0;
	while (token->sub_token && token->sub_token[j])
	{
		new_tmp = ft_strjoin(tmp, token->sub_token[j]->content);
		free(tmp);
		tmp = new_tmp;
		j++;
	}
	free(token->value);
	token->value = tmp;
	add_token(data, token->value, ft_strlen(token->value), TOKEN_WORD);
	j = 0;
	if (token->sub_token)
	{
		while (token->sub_token[j])
		{
			free(token->sub_token[j]->content);
			free(token->sub_token[j]);
			j++;
		}
		free(token->sub_token);
	}
	free(token);
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
