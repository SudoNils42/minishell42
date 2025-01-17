/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:10:21 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/15 14:34:33 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

void	init_data(t_data *data, int ac, char **av, char **env)
{
	data->ac = ac;
	data->av = av;
	data->env = env;
}
