/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:06:44 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/20 14:40:02 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_sub_token(t_sub_token *sub_token)
{
	if (sub_token)
	{
		if (sub_token->content)
		{
			free(sub_token->content);
			sub_token->content = NULL;
		}
		free(sub_token);
		sub_token = NULL;
	}
}

void	free_token(t_token *token)
{
	int	j;

	if (token->sub_tokens)
	{
		j = 0;
		while (token->sub_tokens[j])
		{
			free_sub_token(token->sub_tokens[j]);
			token->sub_tokens[j] = NULL;
			j++;
		}
		free(token->sub_tokens);
		token->sub_tokens = NULL;
	}
	token = NULL;
}

void	free_tokens(t_data *data)
{
	int	i;

	if (data && data->tokens)
	{
		i = 0;
		while (i < data->token_count)
		{
			free_token(&data->tokens[i]);
			if (data->tokens[i].value)
			{
				free(data->tokens[i].value);
				data->tokens[i].value = NULL;
			}
			i++;
		}
		free(data->tokens);
		data->tokens = NULL;
		data->token_count = 0;
	}
}

void	free_command(t_command *command)
{
	if (command)
	{
		if (command->args)
		{
			free(command->args);
			command->args = NULL;
		}
	}
}

void	free_data(t_data *data)
{
	int	i;

	if (data)
	{
		if (data->input)
		{
			free(data->input);
			data->input = NULL;
		}
		if (data->raw_tokens)
		{
			i = 0;
			while (data->raw_tokens[i])
			{
				free(data->raw_tokens[i]);
				data->raw_tokens[i] = NULL;
				i++;
			}
			free(data->raw_tokens);
			data->raw_tokens = NULL;
		}
		if (data->env)
		{
			i = 0;
			while (data->env[i])
			{
				free(data->env[i]);
				data->env[i] = NULL;
				i++;
			}
			free(data->env);
			data->env = NULL;
		}
		if (data->exp)
		{
			i = 0;
			while (data->exp[i])
			{
				free(data->exp[i]);
				data->exp[i] = NULL;
				i++;
			}
			free(data->exp);
			data->exp = NULL;
		}
		if (data->pids)
		{
			free(data->pids);
			data->pids = NULL;
		}
		if (data->command)
		{
			free_command(data->command);
			free(data->command);
			data->command = NULL;
		}
		if (data->tokens)
		{
			free_tokens(data);
			data->tokens = NULL;
		}
	}
}

void	free_all_exit(t_data *data, int exit_code)
{
	(void)data;
	free_data(data);
	printf("exit\n");
	exit(exit_code);
}
