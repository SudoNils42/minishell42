/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:21:23 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/22 19:12:13 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

void	handle_fd(t_data *data)
{
	if (data->command->pipe_read != -1)
	{
		dup2(data->command->pipe_read, STDIN_FILENO);
		close(data->command->pipe_read);
	}
	if (data->command->pipe_write != -1)
	{
		dup2(data->command->pipe_write, STDOUT_FILENO);
		close(data->command->pipe_write);
	}
	if (data->command->input_fd != STDIN_FILENO)
	{
		dup2(data->command->input_fd, STDIN_FILENO);
		close(data->command->input_fd);
	}
	if (data->command->output_fd != STDOUT_FILENO)
	{
		dup2(data->command->output_fd, STDOUT_FILENO);
		close(data->command->output_fd);
	}
}
