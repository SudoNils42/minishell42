/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:23:28 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/21 16:59:22 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data, env);
	start(&data);
	return (0);
}
