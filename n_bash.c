/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_bash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:26:43 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/16 20:14:36 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

int	child_process(t_data *data)
{
	int	i;

	data->pid = fork();
	if (data->pid == 0)
	{
		data->path = getenv("PATH");
		data->dir = ft_split(data->path, ':');
		i = 0;
		while (data->dir[i] != NULL)
		{
			data->full_path = ft_strjoin_with_slash(data->dir[i],
					data->bash_cmd[0]);
			if (access(data->full_path, X_OK) == 0)
			{
				execve(data->full_path, data->bash_cmd, data->env);
				return (1);
			}
			i++;
		}
		printf("%s: command not found\n", *data->bash_cmd);
		exit(1);
	}
	return (0);
}

void	parent_process(t_data *data)
{
	if (data->pid > 0)
		wait(NULL);
	free(data->input_cpy);
}

void	start_bash(t_data *data)
{
	while (1)
	{
		data->input = readline("minishell> ");
		if (!data->input)
			break ;
		add_history(data->input);
		if (ft_strchr(data->input, '|') != 0)
			start_pipe(data);
		else
		{
			data->input_cpy = malloc(strlen(data->input) + 1);
			ft_strcpy(data->input_cpy, data->input);
			data->bash_cmd = ft_split(data->input_cpy, ' ');
			if (child_process(data) == 1)
				break ;
			parent_process(data);
		}
	}
}
