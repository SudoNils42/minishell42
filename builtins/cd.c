/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:25:34 by rabatist          #+#    #+#             */
/*   Updated: 2025/01/30 16:50:34 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_data *data)
{
	char	*home;

	if (!data->command->args[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		chdir(home);
	}
	else
	{
		if (ft_cd2(data))
			return (1);
	}
	update_old_pwd_env(data);
	update_old_pwd_exp(data);
	update_pwd_env(data);
	update_pwd_exp(data);
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
}
