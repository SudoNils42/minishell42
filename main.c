/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:56:15 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/19 18:30:33 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start(t_data *data)
{
	while (1)
	{
		data->input = readline("minishell> ");
		if (!data->input)
		{
			printf("exit\n");
			break ;
		}
		add_history(data->input);
		parsing(data);
		data->current_token = 0;
		process_command_line(data);
		free_tokens(data);
		if (data->pids)
		{
			free(data->pids);
			data->pids = NULL;
		}
		if (data->command)
		{
			free_command(data->command);
			free(data->command);
			data->command = NULL;
		}
		free(data->input);
		data->input = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data);
	make_env(&data, env);
	make_exp(&data, env);
	signals();
	start(&data);
	free_data(&data);
	return (0);
}
