/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:55:53 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/20 17:35:26 by rabatist         ###   ########.fr       */
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
	else if (ft_strcmp(data->command->args[0], "exit") == 0)
		ft_exit(data);
}

int	is_builtin(t_data *data)
{
	char	*cmd;

	if (!data->command->args[0])
		return (0);
	cmd = data->command->args[0];
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
