/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_exec_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:55:53 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/30 16:16:56 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_data *data)
{
	if (ft_strncmp(data->command->args[0], "pwd", 3) == 0)
		data->exit_status = ft_pwd();
	if (ft_strncmp(data->command->args[0], "env", 3) == 0)
		data->exit_status = ft_env(data);
	if (ft_strncmp(data->command->args[0], "echo", 4) == 0)
		data->exit_status = ft_echo(data);
	if (ft_strncmp(data->command->args[0], "cd", 2) == 0)
		data->exit_status = ft_cd(data);
	if (ft_strncmp(data->command->args[0], "export", 6) == 0)
		data->exit_status = ft_export(data);
	if (ft_strncmp(data->command->args[0], "unset", 5) == 0)
		data->exit_status = ft_unset(data);
	if (ft_strncmp(data->command->args[0], "exit", 4) == 0)
		data->exit_status = ft_exit();
}
