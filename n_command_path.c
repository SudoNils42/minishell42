/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_command_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:03:09 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/22 19:03:33 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

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

char	*find_command_path(char *cmd)
{
	char	**path_dirs;
	char	*path_env;
	char	*full_path;
	int		i;

	path_env = getenv("PATH");
	path_dirs = ft_split(path_env, ':');
	i = 0;
	while (path_dirs[i])
	{
		full_path = ft_strjoin_with_slash(path_dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	i = 0;
	return (NULL);
}
