/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:04:22 by nbonnet           #+#    #+#             */
/*   Updated: 2024/10/04 14:52:22 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (dst[i] != '\0')
		i++;
	k = i;
	if (dstsize <= i)
	{
		while (src[j] != '\0')
			j++;
		return (dstsize + j);
	}
	while (src[j] != '\0' && (i < dstsize - 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	while (src[j] != '\0')
		j++;
	return (k + j);
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(int ac, char **av)
{
	(void) ac;
	char dst[35] = "Test1";
	printf("%zu\n", ft_strlcat(av[1], av[2], atoi(av[3])));
	printf("%s\n", av[1]);
	printf("%lu\n", strlcat(dst, "1", 7));
	printf("%s\n", dst);
}
*/
