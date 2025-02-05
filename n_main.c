/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:56:15 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/05 18:56:16 by nbonnet          ###   ########.fr       */
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
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data, env);
	make_env(&data, env);
	make_exp(&data, env);
	signals();
	start(&data);
	return (0);
}
