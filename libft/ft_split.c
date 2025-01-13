/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:58:27 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/13 15:42:04 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strdup1(const char *s1, int start, int len)
{
	int		i;
	char	*s2;

	i = 0;
	start = 0;
	while (start < len)
	{
		i++;
		start++;
	}
	start = 0;
	s2 = malloc(sizeof(char) * (i + 1));
	if (!s2)
		return (0);
	i = 0;
	while (start < len)
	{
		s2[i] = s1[start];
		i++;
		start++;
	}
	s2[len] = '\0';
	return (s2);
}

static int	ft_countwords(char const *s, char c, int i, int j)
{
	int	k;

	k = 0;
	while (s[i] != '\0')
	{
		if ((char)s[i] != c && (char)s[i] != '\0' && j == 0)
		{
			k++;
			j = 1;
		}
		else if ((char)s[i] == c)
			j = 0;
		i++;
	}
	return (k);
}

static void	ft_free(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	ft_tab(char **tab, char const *s, char c, int i)
{
	int	j;
	int	k;

	j = 0;
	while (s[i] != '\0')
	{
		if ((char)s[i] != c)
		{
			k = i;
			while ((char)s[i] != c && s[i] != '\0')
				i++;
			tab[j] = ft_strdup1(&s[k], k, (i - k));
			if (!tab[j])
			{
				ft_free(tab, j);
				return (0);
			}
			j++;
		}
		else
			i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = 0;
	j = 0;
	k = ft_countwords(s, c, i, j);
	tab = (char **)malloc(sizeof(char *) * (k + 1));
	if (!tab)
		return (0);
	tab[k] = NULL;
	while (j < k)
	{
		i = ft_tab(tab, s, c, i);
		if (i == 0)
			return (0);
		j++;
	}
	return (tab);
}
/*
#include <stdio.h>
int	main(void)
{
	char const	s[] = "salut,ca,,,va,?";
	char		c = ',';
	char 		**result = ft_split(s, c);
	int			i = 0;

	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		i++;
	}
	return (0);
}
*/
