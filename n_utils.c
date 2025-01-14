/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:21:23 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/14 17:44:53 by nbonnet          ###   ########.fr       */
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

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next;
	char		*token;

	if (str)
		next = str;
	if (!next || !*next)
		return (NULL);
	while (*next && (ft_strncmp(delim, next, 1) == 0))
		next++;
	if (!*next)
		return (NULL);
	token = next;
	while (*next && (ft_strncmp(delim, next, 1) != 0))
		next++;
	if (*next)
	{
		*next = '\0';
		next++;
	}
	return (token);
}
