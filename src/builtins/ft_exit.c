/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:44:17 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/01 11:42:28 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_valid_exit_argument(char *arg)
{
    if (!arg || *arg == '\0')
        return (false);
    if (*arg == '-')
        ++arg;

    while (*arg)
    {
        if (!isdigit((unsigned char)*arg))
            return (false);
        ++arg;
    }
    return (true);
}

bool ft_exit(char **args, t_minishell *shell)
{
    int exit_status = 0;

    free_memory(shell);

    if (args[1])
    {
        if (is_valid_exit_argument(args[1]) && !args[2])
            exit_status = ft_atoi(args[1]);
        else
        {
            if (!is_valid_exit_argument(args[1]))
            {
                ft_printf("exit: %s: numeric argument required\n", args[1]);
                exit_status = 255;
            }
            else
            {
                ft_printf("exit: too many arguments\n");
                return (true); 
            }
        }
    }

    ft_printf("exit\n");
    exit(exit_status);
}
