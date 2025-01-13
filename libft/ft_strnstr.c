/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:19:31 by nbonnet           #+#    #+#             */
/*   Updated: 2024/10/11 11:53:51 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	j = 0;
	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[j] != '\0' && j < len)
	{
		i = 0;
		ptr = (char *)(haystack + j);
		while (needle[i] != '\0' && (j + i) < len)
		{
			if (needle[i] == haystack[j + i])
				i++;
			else
				break ;
			if (needle[i] == '\0')
				return (ptr);
		}
		j++;
	}
	return (0);
}

/*
#include <stdio.h>
int	main(void)
{
	const char	haystack[] = "aaabcabcd";
	const char	needle[] = "bc";
	size_t	len = 8;

	char *result = ft_strnstr(haystack, needle, len);
	char *result1 = strnstr(haystack, needle, len);

	printf("%s\n", result);
	printf("%s\n", result1);
	return (0);
}
*/
