/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:11:24 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/31 15:38:49 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_env(t_data *data, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		exit(1);
	j = -1;
	while (++j < i)
		data->env[j] = ft_strdup(env[j]);
	data->env[i] = NULL; 
}

void	make_exp(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->exp = malloc(sizeof(char *) * (i + 1));
	if (!data->exp)
		exit(1);
	i = 0;
	while (env[i])
	{
		data->exp[i] = ft_strdup(env[i]);
		if (!data->exp[i])
		{
			while (--i >= 0)
				free(data->exp[i]);
			free(data->exp);
			exit(1);
		}
		i++;
	}
}
