/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:37:22 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/30 15:39:27 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

int    ft_echo(t_data *data)
{
    int    i;
    int    line;
    int    j;

    i = 1;
    line = 1;
    while (data->command->args[i] && data->command->args[i][0] == '-' && data->command->args[i][1] == 'n')
    {
        j = 1;
        while (data->command->args[i][j] == 'n')
            j++;
        if (data->command->args[i][j] == '\0')
        {
            line = 0;
            i++;
        }
        else
            break ;
    }
    ft_echo_print(data, i, line);
    return (0);
}

void    ft_echo_print(t_data *data, int i, int line)
{
    while (data->command->args[i] != NULL)
    {
        printf("%s", data->command->args[i]);
        i++;
        if (data->command->args[i] != NULL)
            printf(" ");
    }
    if (line)
        printf("\n");
}
