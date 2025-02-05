/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:29:47 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/05 18:14:55 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signals(int new)
{
	static int value;

	if (new == -1)
		return (value);
	value = new;
	return (value);
}

void	sig_int(int signal)
{
	
	(void)signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (!g_signals(-1))
		rl_redisplay();
}

void	signals(void)
{
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, SIG_IGN);
}
