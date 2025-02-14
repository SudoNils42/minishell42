/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:06:44 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/15 00:58:05 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	free_all(t_data *data)
{
	int	i;
	int	j;

	if (data->env)
	{
		i = 0;
		while (data->env[i])
			free(data->env[i++]);
		free(data->env);
		data->env = NULL;
	}
	if (data->exp)
	{
		i = 0;
		while (data->exp[i])
			free(data->exp[i++]);
		free(data->exp);
		data->exp = NULL;
	}
	if (data->tokens)
	{
		i = -1;
		while (++i < data->token_count)
		{
			free(data->tokens[i].value);
			if (data->tokens[i].sub_tokens)
			{
				j = -1;
				while (data->tokens[i].sub_tokens[++j])
				{
					free(data->tokens[i].sub_tokens[j]->content);
					free(data->tokens[i].sub_tokens[j]);
				}
				free(data->tokens[i].sub_tokens);
				data->tokens[i].sub_tokens = NULL;
			}
		}
		free(data->tokens);
		data->tokens = NULL;
		data->token_count = 0;
	}
	if (data->command)
	{
		if (data->command->args)
			free(data->command->args);
		free(data->command);
		data->command = NULL;
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->content)
	{
		free(data->content);
		data->content = NULL;
	}
} */
void	free_all_exit(t_data *data, int exit_code)
{
	(void)data;
	printf("exit\n");
	exit(exit_code);
}
