/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:04:22 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/13 16:33:25 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in(t_data *data, int token_count)
{
	char	*filename;

	if (data->tokens[data->current_token].type == TOKEN_REDIRECT_IN)
	{
		if (data->current_token + 1 >= token_count)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
				2);
			return (-1);
		}
		filename = data->tokens[data->current_token + 1].value;
		data->command->input_fd = open(filename, O_RDONLY);
		if (data->command->input_fd == -1)
		{
			perror("minishell");
			return (-1);
		}
		return (2);
	}
	return (0);
}

int	redirect_out(t_data *data, int token_count)
{
	char	*filename;

	if (data->tokens[data->current_token].type == TOKEN_REDIRECT_OUT)
	{
		if (data->current_token + 1 >= token_count)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
				2);
			return (-1);
		}
		filename = data->tokens[data->current_token + 1].value;
		data->command->output_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->command->output_fd == -1)
		{
			perror("minishell");
			return (-1);
		}
		return (2);
	}
	return (0);
}

int	redirect_append(t_data *data, int token_count)
{
	char	*filename;

	if (data->tokens[data->current_token].type == TOKEN_REDIRECT_APPEND)
	{
		if (data->current_token + 1 >= token_count)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
				2);
			return (-1);
		}
		filename = data->tokens[data->current_token + 1].value;
		data->command->output_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (data->command->output_fd == -1)
		{
			perror("minishell");
			return (-1);
		}
		return (2);
	}
	return (0);
}

int	redirect_heredoc(t_data *data, int token_count)
{
	char	*delimiter;
	int		pipe_fd[2];
	char	*line;

	if (data->tokens[data->current_token].type != TOKEN_HEREDOC)
		return (0);
	if (data->current_token + 1 >= token_count)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (-1);
	}
	delimiter = data->tokens[data->current_token + 1].value;
	pipe(pipe_fd);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
	}
	close(pipe_fd[1]);
	data->command->input_fd = pipe_fd[0];
	return (2);
}

int	handle_redirection(t_data *data)
{
	int	processed;

	processed = redirect_in(data, data->token_count);
	if (processed != 0)
		return (process_redirection(processed, data));
	processed = redirect_out(data, data->token_count);
	if (processed != 0)
		return (process_redirection(processed, data));
	processed = redirect_append(data, data->token_count);
	if (processed != 0)
		return (process_redirection(processed, data));
	processed = redirect_heredoc(data, data->token_count);
	if (processed != 0)
		return (process_redirection(processed, data));
	return (0);
}
