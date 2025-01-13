/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:16:51 by nbonnet           #+#    #+#             */
/*   Updated: 2024/10/08 12:56:18 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_itoa1(void)
{
	char	*dst;

	dst = (char *)malloc(sizeof(char) * 12);
	if (!dst)
		return (0);
	dst[0] = '-';
	dst[1] = '2';
	dst[2] = '1';
	dst[3] = '4';
	dst[4] = '7';
	dst[5] = '4';
	dst[6] = '8';
	dst[7] = '3';
	dst[8] = '6';
	dst[9] = '4';
	dst[10] = '8';
	dst[11] = '\0';
	return (dst);
}

static	char	*ft_itoa2(void)
{
	char	*dst;

	dst = (char *)malloc(sizeof(char) * 2);
	if (!dst)
		return (0);
	dst[0] = '0';
	dst[1] = '\0';
	return (dst);
}

static int	nbrlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i = 1;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*dst;

	if (n == -2147483648)
		return (ft_itoa1());
	if (n == 0)
		return (ft_itoa2());
	i = nbrlen(n);
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (0);
	if (n < 0)
	{
		dst[0] = '-';
		n *= -1;
	}
	dst[i] = '\0';
	i = i - 1;
	while (n != 0)
	{
		dst[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (dst);
}
/**
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int n;

    n = -12345;
    printf("%s\n", ft_itoa(n));
    return (0);
}
*/
