/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:29:23 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/14 23:49:13 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *str, t_data *data)
{
	int		i;
	char	*value;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], str, ft_strlen(str)) == 0
			&& data->env[i][ft_strlen(str)] == '=')
		{
			value = ft_strdup(data->env[i] + ft_strlen(str) + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

void	get_exit_status(t_data *data, int i)
{
	char	*exit_status;

	exit_status = ft_itoa(data->exit_status);
	free(data->command->args[i]);
	data->command->args[i] = exit_status;
}
