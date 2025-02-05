/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_expand_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:24 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/06 00:43:27 by nbonnet          ###   ########.fr       */
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

char	*expand_variables(char *str, t_data *data)
{
	char	*result;
	char	*tmp;
	int		i;
	char	*exit_str;
	int		j;
	char	*var;
	char	*env_val;
	char	buf[2];

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			exit_str = ft_itoa(data->exit_status);
			tmp = ft_strjoin(result, exit_str);
			free(result);
			result = tmp;
			free(exit_str);
			i += 2;
		}
		else if (str[i] == '$')
		{
			i++;
			j = i;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			var = ft_substr(str, i, j - i);
			env_val = get_env_value(var, data);
			if (!env_val)
				env_val = ft_strdup("");
			tmp = ft_strjoin(result, env_val);
			free(result);
			result = tmp;
			free(var);
			free(env_val);
			i = j;
		}
		else
		{
			buf[0] = str[i];
			buf[1] = '\0';
			tmp = ft_strjoin(result, buf);
			free(result);
			result = tmp;
			i++;
		}
	}
	return (result);
}

