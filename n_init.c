/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:10:21 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/22 17:58:04 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

void	init_data(t_data *data, char **env)
{
	data->env = env;
	data->tokens = NULL;
	data->token_count = 0;
	data->current_token = 0;
	data->command = NULL;
	data->input = NULL;
	data->next_pipe_read = -1;
}
