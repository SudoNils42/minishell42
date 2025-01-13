/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:17:09 by nbonnet           #+#    #+#             */
/*   Updated: 2024/10/07 11:19:42 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s[i] && (char)c != '\0')
		return (0);
	if (s[i] == '\0')
		return ((char *)(s + i));
	while (s[i] != '\0')
	{
		i++;
	}
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			return ((char *)(s + i));
		}
		i--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{s
	const char s[] = "";
	int	c = 108;

	char *ptr1 = ft_strrchr(s, c);
	char *ptr2 = strrchr(s, c);

	printf("%s\n", ptr1);
	printf("%s\n", ptr2);
	return 0;

}
*/
