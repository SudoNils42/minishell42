/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:39:09 by rabatist          #+#    #+#             */
/*   Updated: 2025/01/30 16:09:52 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_with_equal(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], str, ft_strchr(str, '=') - str)
			&& data->env[i][ft_strchr(str, '=') - str] == '=')
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(str);
			return ;
		}
		i++;
	}
	data->env[i] = ft_strdup(str);
	data->env[i + 1] = NULL;
}

void	update_exp_with_equal(t_data *data, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strchr(str, '=') - str;
	while (data->exp[i])
	{
		if (!ft_strncmp(data->exp[i], str, len)
			&& (data->exp[i][len] == '=' || data->exp[i][len] == '\0'))
		{
			free (data->exp[i]);
			data->exp[i] = ft_strdup(str);
			return ;
		}
		i++;
	}
	data->exp[i] = ft_strdup(str);
	data->exp[i + 1] = NULL;
}

void	valid_var_name(t_data *data, int i)
{
	if (ft_strchr(data->command->args[i], '='))
	{
		update_env_with_equal(data, data->command->args[i]);
		update_exp_with_equal(data, data->command->args[i]);
	}
	else
		update_exp_without_equal(data, data->command->args[i]);
}
