/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:55:15 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/22 18:44:04 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(t_envp **l_envp, char *var_name)
{
	t_envp	*current;
	t_envp	*prev;

	current = *l_envp;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*l_envp = current->next;
			free(current->name);
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

bool	ft_unset(char **args, t_minishell *shell)
{
	int	i;

	i = 1;
	if (!args || !shell)
		return (false);
	while (args[i])
	{
		remove_env_var(&(shell->l_envp), args[i]);
		i++;
	}
	return (true);
}
