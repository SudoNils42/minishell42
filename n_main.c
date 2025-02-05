/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:23:28 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/05 18:28:19 by rabatist         ###   ########.fr       */
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
		if (!check_args(data->input))
			continue ;
		add_history(data->input);
		data->tokens = tokenize_input(data);
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
