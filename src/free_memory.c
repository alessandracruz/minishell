/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:53:20 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/23 23:05:25 by acastilh         ###   ########.fr       */
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

void	free_cmd_node(t_cmd_node *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->arg_count)
	{
		free(cmd->args[i]);
		i++;
	}
	free_redirection(cmd->input_redirection);
	free_redirection(cmd->output_redirection);
	free(cmd);
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
	{
		free_env_list(shell->l_envp);
		if (shell->current_cmd != NULL)
		{
			free_cmd_node(shell->current_cmd);
		}
	}
}
