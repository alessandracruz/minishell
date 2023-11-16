/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:32:33 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/15 18:44:57 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execute_builtin(char **args, t_minishell *shell)
{
	if (args == NULL || args[0] == NULL)
		return (false);
	if (strcmp(args[0], "cd") == 0)
	{
		ft_cd(args, shell);
		return (true);
	}
	return (false);
}
