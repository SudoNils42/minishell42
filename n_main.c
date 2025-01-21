/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:23:28 by nbonnet           #+#    #+#             */
/*   Updated: 2025/01/21 15:44:29 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_minishell.h"

int main(int ac, char **av, char **env)
{
    t_data  data;

    (void)ac;
    (void)av;

    init_data(&data, env);
    data.max_pids = 10;  // Taille initiale
    data.all_pids = malloc(sizeof(int) * data.max_pids);

    while (1)
    {
        data.input = readline("minishell> ");
        if (!data.input)
            break;
        if (data.input[0] != '\0')
            add_history(data.input);

        data.tokens = tokenize_input(data.input, &data.token_count);
        if (data.tokens)
        {
            data.current_token = 0;
            process_command_line(&data);
            free_tokens(data.tokens, data.token_count);
        }
        free(data.input);
    }

    free(data.all_pids);
    return (0);
}
