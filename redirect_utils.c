/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:22:40 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/21 15:31:47 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_redirection(int processed, t_data *data)
{
	if (processed == -1)
		return (-1);
	data->current_token += processed;
	return (processed);
}

void	inside_heredoc(char *delimiter, int pipe_fd[2])
{
	static int	i = 0;
	char		*line;

	while (1)
	{
		i++;
		line = readline("> ");
		if (line == 0)
		{
			printf("minishell: warning: here-document at line %d delimited", i);
			printf(" by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
	}
	close(pipe_fd[1]);
}

void	print_first_error(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	print_error(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}
