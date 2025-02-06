/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:06:56 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/06 19:18:11 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bubble_sort(char **env)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	size = 0;
	i = 0;
	while (env[size])
		size++;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	is_valid_var_name(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_without_args(t_data *data)
{
	int		i;
	char	*sign;

	bubble_sort(data->exp);
	i = 0;
	while (data->exp[i])
	{
		sign = ft_strchr(data->exp[i], '=');
		if (sign)
			printf("declare -x %.*s=\"%s\"\n",
				(int)(sign - data->exp[i]), data->exp[i], sign + 1);
		else
			printf("declare -x %s\n", data->exp[i]);
		i++;
	}
}

void	update_exp_without_equal(t_data *data, char *str)
{
	int		i;
	char	**new_exp;
	int		j;

	i = 0;
	j = -1;
	while (data->exp[i])
	{
		if (!ft_strncmp(data->exp[i], str, ft_strlen(str))
			&& (data->exp[i][ft_strlen(str)] == '='
			|| data->exp[i][ft_strlen(str)] == '\0'))
			return ;
		i++;
	}
	new_exp = malloc(sizeof(char *) * (i + 2));
	if (!new_exp)
		return ;
	while (++j < i)
		new_exp[j] = data->exp[j];
	new_exp[i] = ft_strdup(str);
	new_exp[i + 1] = NULL;
	free (data->exp);
	data->exp = new_exp;
}

int	ft_export(t_data *data)
{
	int	i;

	i = 0;
	if (!data->command->args[1])
	{
		export_without_args(data);
		return (0);
	}
	while (data->command->args[++i])
	{
		if (is_valid_var_name(data->command->args[i]))
			valid_var_name(data, i);
		else
		{
			write (2, "export: ", 8);
			write (2, data->command->args[1], ft_strlen(data->command->args[1]));
			write (2, "': not a valid identifier\n", 26);
			return (1);
		}
	}
	return (0);
}
