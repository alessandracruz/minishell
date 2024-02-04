/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:32:33 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/03 20:58:28 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_builtin(char *cmd)
{
    if (cmd == NULL)
    {
        return (false);
    }
    if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
    {
        return (true);
    }
    if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
    {
        return (true);
    }
    if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
    {
        return (true);
    }
    if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
    {
        return (true);
    }
    return (false);
}

bool execute_builtin(char **args, t_minishell *shell)
{
    if (args == NULL || args[0] == NULL)
    {
        return (false);
    }
    if (ft_strcmp(args[0], "cd") == 0)
    {
        return (ft_cd(args, shell));
    }
    if (ft_strcmp(args[0], "echo") == 0)
    {
        return (ft_echo(args, shell));
    }
    if (ft_strcmp(args[0], "pwd") == 0)
    {
        return (ft_pwd(shell));
    }
    if (ft_strcmp(args[0], "env") == 0)
    {
        return (ft_env(shell));
    }
    return (false);
}

