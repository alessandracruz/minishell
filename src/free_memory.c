/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:53:20 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/15 15:34:47 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_envp *env_list)
{
	t_envp	*temp;

	while (env_list != NULL)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->name);
		free(temp->value);
		free(temp->full);
		free(temp);
	}
}

void	free_memory(t_minishell *shell)
{
	if (shell != NULL)
	{
		free_env_list(shell->l_envp);
        // Adicione aqui a liberação de outras estruturas de dados, se necessário
    }
}
