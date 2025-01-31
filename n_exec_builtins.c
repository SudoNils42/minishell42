/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_exec_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:55:53 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/31 14:23:47 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_data *data)
{
	if (ft_strcmp(data->command->args[0], "pwd") == 0)
		data->exit_status = ft_pwd();
	else if (ft_strcmp(data->command->args[0], "env") == 0)
		data->exit_status = ft_env(data);
	else if (ft_strcmp(data->command->args[0], "echo") == 0)
		data->exit_status = ft_echo(data);
	else if (ft_strcmp(data->command->args[0], "cd") == 0)
		data->exit_status = ft_cd(data);
	else if (ft_strcmp(data->command->args[0], "export") == 0)
		data->exit_status = ft_export(data);
	else if (ft_strcmp(data->command->args[0], "unset") == 0)
		data->exit_status = ft_unset(data);
	else if (ft_strcmp(data->command->args[0], "exit")== 0)
		data->exit_status = ft_exit();
}
