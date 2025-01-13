/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:07:58 by nbonnet           #+#    #+#             */
/*   Updated: 2024/10/07 19:42:28 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strtrim1(char const *s1)
{
	int		i;
	int		k;
	char	*dst;

	i = 0;
	k = ft_strlen(s1) - 1;
	dst = (char *)malloc(sizeof(char) * (k + 2));
	if (!dst)
		return (0);
	while (s1[i])
	{
		dst[i] = (char)s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	ft_strtrim2(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && set[j] != '\0')
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static int	ft_strtrim3(char const *s1, char const *set, int i, int j)
{
	int	k;

	k = ft_strlen(s1) - 1;
	while (k > i && set[j] != '\0')
	{
		if (s1[k] == set[j])
		{
			k--;
			j = 0;
		}
		else
			j++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*dst;

	j = 0;
	k = ft_strlen(s1) - 1;
	if (set[0] == '\0')
		return (ft_strtrim1(s1));
	i = ft_strtrim2(s1, set);
	k = ft_strtrim3(s1, set, i, j);
	dst = (char *)malloc(sizeof(char) * (k - i + 2));
	if (!dst)
		return (0);
	j = 0;
	while (i <= k)
		dst[j++] = s1[i++];
	dst[j] = '\0';
	return (dst);
}

/*
#include <stdio.h>
int main(void)
{
	char const	s1[] = "";
	char const set[] = "";

	printf("%s\n", ft_strtrim(s1, set));
	return 0;
}
*/
