/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:03:09 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/19 15:14:01 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_with_slash(const char *s1, const char *s2)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s2);
	free(tmp);
	return (result);
}

char	*find_command_path(char *cmd, t_data *data)
{
	char	**path_dirs;
	char	*path_env;
	char	*full_path;
	int		i;
	int		j;

	if (!cmd || !data)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = find_path(data);
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	free(path_env);
	i = 0;
	while (path_dirs[i])
	{
		full_path = ft_strjoin_with_slash(path_dirs[i], cmd);
		if (!full_path)
		{
			j = 0;
			while (path_dirs[j])
			{
				free(path_dirs[j]);
				j++;
			}
			free(path_dirs);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			j = 0;
			while (path_dirs[j])
			{
				free(path_dirs[j]);
				j++;
			}
			free(path_dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	j = 0;
	while (path_dirs[j])
	{
		free(path_dirs[j]);
		j++;
	}
	free(path_dirs);
	return (NULL);
}

char	*find_path(t_data *data)
{
	char	*path;
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(data->env[i]);
			break ;
		}
		i++;
	}
	return (path);
}
