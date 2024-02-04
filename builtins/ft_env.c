/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:12:46 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/03 20:50:56 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ft_env(t_minishell *shell)
{
    t_envp *current;

    current = shell->l_envp;
    while (current != NULL)
    {
        if (current->name && current->value)
        {
            ft_printf("%s=%s\n", current->name, current->value);
        }
        current = current->next;
    }
    return (true);
}

