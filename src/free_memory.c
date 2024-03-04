/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:53:20 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/04 10:35:05 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirection(t_redirection *redir)
{
	if (redir)
	{
		free(redir->type);
		free(redir->filename);
		free(redir);
	}
}

void	free_env_list(t_envp *env_list)
{
	t_envp	*temp;

	while (env_list != NULL)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

void	free_memory(t_minishell *shell)
{
	if (shell != NULL)
		free_env_list(shell->l_envp);
}
