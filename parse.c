/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:24 by rabatist          #+#    #+#             */
/*   Updated: 2025/01/31 16:32:02 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args(char *str)
{
	if (!is_quotes_open(str))
		return (1);
	return (0);
}

int	is_quotes_open(char *str)
{
	int	in_one;
	int	in_two;
	int	i;

	in_one = 0;
	in_two = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_two)
			in_one = !in_one;
		else if (str[i] == '\"' && !in_one)
			in_two = !in_two;
		i++;
	}
	if (in_one || in_two)
	{
		printf("Error: quotes bot closed\n");
		return (1);
	}
	return (0);
}

void	check_dollars(t_data *data)
{
	int		i;
	char	*str;
	char	*env_value;

	i = -1;
	while (data->command->args[++i])
	{
		if (data->command->args[i][0] == '$')
		{
			if (data->command->args[i][1] == '?')
				get_exit_status(data, i);
			else
			{
				str = data->command->args[i] + 1;
				env_value = get_env_value(str, data);
				if (env_value != NULL)
				{
					free (data->command->args[i]);
					data->command->args[i] = env_value;
				}
				else
					data->command->args[i] = ft_strdup("");
			}
		}
	}
}

void	get_exit_status(t_data *data, int i)
{
	char	*exit_status;

	exit_status = ft_itoa(data->exit_status);
	free (data->command->args[i]);
	data->command->args[i] = exit_status;
}

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
