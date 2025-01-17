/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:21:23 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/16 20:14:43 by nbonnet          ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
