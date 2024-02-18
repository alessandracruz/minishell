/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:55:15 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/16 20:35:27 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    ft_unset(char **args, t_minishell *shell)
{
    int i;
    t_envp *current;
    t_envp *prev;

    i = 1;
    if (!args || !shell)
        return (false);
    while (args[i])
    {
        current = shell->l_envp;
        prev = NULL;
        while (current)
        {
            if (ft_strcmp(current->name, args[i]) == 0)
            {
                if (prev)
                    prev->next = current->next;
                else
                    shell->l_envp = current->next;
                free(current->name);
                free(current->value);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
    return (true);
}
