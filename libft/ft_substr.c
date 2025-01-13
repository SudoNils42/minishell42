/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:32:45 by nbonnet           #+#    #+#             */
/*   Updated: 2024/10/07 16:06:07 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dst;

	j = 0;
	i = ft_strlen(s);
	if (start >= (unsigned int)i)
	{
		dst = malloc(sizeof(char) * 1);
		if (!dst)
			return (0);
		dst[0] = '\0';
		return (dst);
	}
	if (len >= i - start)
		len = i - start;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	i = start;
	while (s[i] != '\0' && j < len)
		dst[j++] = s[i++];
	dst[j] = '\0';
	return (dst);
}
/*
#include <stdio.h>
int main(void)
{
	char const s[] = "tripouille";
	unsigned int start = 400;
	size_t	len = 20;

	printf("%s\n", ft_substr(s, start, len));
	return 0;
}
*/
