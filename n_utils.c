/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:21:23 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/22 17:50:34 by nbonnet          ###   ########.fr       */
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

void	ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

void	free_tokens(t_token *tokens, int count)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (i < count)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	free(cmd);
}
