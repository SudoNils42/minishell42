/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:39:23 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/07 17:56:06 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_data *data)
{
	int	nbr;

	if (data->command->args[1])
		nbr = ft_exit2(data);
	if (data->command->args[1] && data->command->args[2])
	{
		write (2, "bash: exit: too many arguments\n", 30);
		data->exit_status = 1;
		return ;
	}
	if (!data->command->args[1])
		free_all_exit (data->exit_status);
	free_all_exit (nbr);
}

int	ft_exit2(t_data *data)
{
	int	nbr;

	if (!is_valid_exit_argument(data->command->args[1]))
	{
		write (2, "bash: exit: ", 12);
		write (2, data->command->args[1], ft_strlen(data->command->args[1]));
		write (2, ": numeric argument required\n", 28);
		data->exit_status = 2;
		free_all_exit (data->exit_status);
	}
	nbr = ft_ratoi(data->command->args[1]);
	if (nbr == -1)
	{
		write (2, "bash: exit: ", 12);
		write (2, data->command->args[1], ft_strlen(data->command->args[1]));
		write (2, ": numeric argument required\n", 28);
		data->exit_status = 2;
		free_all_exit(data->exit_status);
	}
	return (nbr);
}

int	is_valid_exit_argument(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_ratoi(char *str)
{
	int			i;
	long long	nbr;
	int			sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (nbr > LONG_MAX)
		return (-1);
	nbr *= sign;
	return ((int)(nbr % 256));
}
