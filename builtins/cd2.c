/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:50 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/06 19:49:52 by rabatist         ###   ########.fr       */
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
	update_pwd_exp(data);
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

void	ft_cd2(t_data *data)
{
	char	*home;
	
	home = ft_get_home(data);
	if (!home)
	{
		write (2, "cd: HOME not set\n", 17);
	}
	else if (chdir(home)!= 0)
	{
		write (2, "cd: ", 4);
		write (2, home, ft_strlen(home));
		write (2, ": No such file or directory\n", 28);
	}
}

int	ft_cd3(t_data *data)
{
	struct stat	statbuf;

	if (stat(data->command->args[1], &statbuf) == -1)
	{
		perror ("cd");
		return (1);
	}
	else if (!(statbuf.st_mode & S_IFDIR))
	{
		write (2, "cd: ", 4);
		write (2, data->command->args[1], ft_strlen(data->command->args[1]));
		write (2, ": Not a directory\n", 18);
		return (1);
	}
	else
	{
		if (chdir(data->command->args[1]) != 0)
		{
			perror ("cd");
			return (1);
		}
	}
	return (0);
}

char	*ft_get_home(t_data *data)
{
	int		i;
	char	*home;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
		{
			home = ft_strchr(data->env[i], '=');
			if (home)
				return (home + 1);
		}
		i++;
	}
	return (NULL);
}
