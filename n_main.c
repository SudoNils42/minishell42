/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:23:28 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/16 20:14:51 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	init_data(&data, ac, av, env);
	start_bash(&data);
	return (0);
}
