/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:32:33 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/01 14:42:24 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (false);
	if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		return (true);
	if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		return (true);
	if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		return (true);
	if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		return (true);
	if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		return (true);
	if (!ft_strncmp(cmd, "env", ft_strlen("env")))
		return (true);
	if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		return (true);
	return (false);
}

bool	execute_builtin(char **args, t_minishell *shell)
{
	if (args == NULL || args[0] == NULL)
		return (false);
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args, shell));
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, shell));
	if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(shell));
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, shell));
	if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, shell));
	if (!ft_strcmp(args[0], "env"))
		return (ft_env(shell));
	if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, shell));
	return (false);
}
