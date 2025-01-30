/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:50 by rabatist          #+#    #+#             */
/*   Updated: 2025/01/30 16:09:10 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd_env(t_data *data)
{
	char	cwd[PATH_MAX];
	int		i;

	i = 0;
	if (getcwd(cwd, PATH_MAX))
	{
		while (data->env[i])
		{
			if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
			{
				free (data->env[i]);
				data->env[i] = malloc(sizeof(char) * (ft_strlen(cwd) + 5));
				if (!data->env[i])
					return ;
				ft_strlcpy(data->env[i], "PWD=", 5);
				ft_strlcat(data->env[i], cwd, ft_strlen(cwd) + 5);
				return ;
			}
			i++;
		}
	}
}

void	update_pwd_exp(t_data *data)
{
	char	cwd[PATH_MAX];
	int		i;

	i = 0;
	if (getcwd(cwd, PATH_MAX))
	{
		while (data->exp[i])
		{
			if (ft_strncmp(data->exp[i], "PWD=", 4) == 0)
			{
				free (data->exp[i]);
				data->exp[i] = malloc(sizeof(char) * (ft_strlen(cwd) + 5));
				if (!data->exp[i])
					return ;
				ft_strlcpy(data->exp[i], "PWD=", 5);
				ft_strlcat(data->exp[i], cwd, ft_strlen(cwd) + 5);
				return ;
			}
			i++;
		}
	}
}

int	ft_cd2(t_data *data)
{
	struct stat	statbuf;

	if (stat(data->command->args[1], &statbuf) == -1)
	{
		printf("cd: %s: No such file or directory\n", data->command->args[1]);
		return (1);
	}
	else if (!(statbuf.st_mode & S_IFDIR))
	{
		printf("cd: %s: Not a directory\n", data->command->args[1]);
		return (1);
	}
	else
		chdir(data->command->args[1]);
	return (0);
}
