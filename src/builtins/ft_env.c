/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:12:46 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/03 20:48:24 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_env(t_minishell *shell)
{
	t_envp	*current;

	current = shell->l_envp;
	while (current != NULL)
	{
		if (current->name && current->value)
			ft_printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (true);
}
