/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:12:13 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/10 17:04:24 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_free(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

int	free_cmds(t_cmd **cmds)
{
	t_cmd	*cmd;
	t_cmd	*pointer;

	cmd = *cmds;
	while (cmd)
	{
		pointer = cmd->next;
		free(cmd->cmd);
		if (cmd)
			free(cmd);
		cmd = pointer;
	}
	return (-1);
}
