/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:32:33 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/16 12:02:49 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execute_builtin(char **args, t_minishell *shell)
{
	if (args == NULL || args[0] == NULL)
		return (false);
	if (strcmp(args[0], "cd") == 0)
		return (ft_cd(args, shell));
	if (strcmp(args[0], "echo") == 0)
		return (ft_echo(args, shell));
	return (false);
}
