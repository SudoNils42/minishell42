/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:25:34 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/06 19:49:45 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_data *data)
{
	if (data->command->args[2])
	{
		write (2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (!data->command->args[1])
	{
		ft_cd3(data);
		return (1);
	}
	else
	{
		if (ft_cd3(data))
			return (1);
	}
	update_old_pwd_env(data);
	return (0);
}

void	update_old_pwd_env(t_data *data)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			pwd = ft_strchr(data->env[i], '=') + 1;
			break ;
		}
		i++;
	}
	if (!pwd)
		return ;
	update_old_pwd_env2(data, pwd);
}

void	update_old_pwd_env2(t_data *data, char *pwd)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
		{
			free(data->env[i]);
			data->env[i] = malloc(sizeof(char) * (ft_strlen(pwd) + 8));
			if (!data->env[i])
				return ;
			ft_strlcpy(data->env[i], "OLDPWD=", 8);
			ft_strlcat(data->env[i], pwd, ft_strlen(pwd) + 8);
			return ;
		}
		i++;
	}
	update_old_pwd_exp(data);
}

void	update_old_pwd_exp(t_data *data)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = NULL;
	while (data->exp[i])
	{
		if (ft_strncmp(data->exp[i], "PWD=", 4) == 0)
		{
			pwd = ft_strchr(data->exp[i], '=') + 1;
			break ;
		}
		i++;
	}
	if (!pwd)
		return ;
	update_old_pwd_exp2(data, pwd);
}

void	update_old_pwd_exp2(t_data *data, char *pwd)
{
	int	i;

	i = 0;
	while (data->exp[i])
	{
		if (ft_strncmp(data->exp[i], "OLDPWD=", 7) == 0)
		{
			free(data->exp[i]);
			data->exp[i] = malloc(sizeof(char) * (ft_strlen(pwd) + 8));
			if (!data->exp[i])
				return ;
			ft_strlcpy(data->exp[i], "OLDPWD=", 8);
			ft_strlcat(data->exp[i], pwd, ft_strlen(pwd) + 8);
			return ;
		}
		i++;
	}
	update_pwd_env(data);
}
