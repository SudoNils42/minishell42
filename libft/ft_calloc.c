/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:09:24 by nbonnet           #+#    #+#             */
/*   Updated: 2024/10/04 16:11:21 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ptr;

	i = 0;
	ptr = malloc(size * count);
	if (!ptr)
		return (0);
	while (i < count * size)
	{
		((unsigned char *)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	size_t count = 43;
	size_t size = 34;

	char	*result;
	char	*result1;

	result = ft_calloc(count, size);
	result1 = calloc(count, size);

	printf("%p,\n", result);
	printf("%p,\n", result1);
	return(0);
}
*/
