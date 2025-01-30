/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:26:13 by rabatist          #+#    #+#             */
/*   Updated: 2025/01/30 16:10:08 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_var_in_env(t_data *data, char *var_name)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = 0;
	while (data->env[len])
		len++;
	while (++i < len)
	{
		if (ft_strncmp(data->env[i], var_name, ft_strlen(var_name)) == 0
			&& (data->env[i][ft_strlen(var_name)] == '='
			|| data->env[i][ft_strlen(var_name)] == '\0'))
		{
			free (data->env[i]);
			j = i;
			while (j < len - 1)
			{
				data->env[j] = data->env[j + 1];
				j++;
			}
			data->env[len - 1] = NULL;
			break ;
		}
	}
}

void	unset_var_in_exp(t_data *data, char *var_name)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = 0;
	while (data->exp[len])
		len++;
	while (++i < len)
	{
		if (ft_strncmp(data->exp[i], var_name, ft_strlen(var_name)) == 0
			&& (data->exp[i][ft_strlen(var_name)] == '='
			|| data->exp[i][ft_strlen(var_name)] == '\0'))
		{
			free (data->exp[i]);
			j = i;
			while (j < len - 1)
			{
				data->exp[j] = data->exp[j + 1];
				j++;
			}
			data->exp[len - 1] = NULL;
			break ;
		}
	}
}

int	ft_unset(t_data *data)
{
	int	i;

	i = 0;
	while (data->command->args[i])
	{
		unset_var_in_env(data, data->command->args[i]);
		unset_var_in_exp(data, data->command->args[i]);
		i++;
	}
	return (0);
}
