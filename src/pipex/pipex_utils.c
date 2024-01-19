/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:20:43 by matlopes          #+#    #+#             */
/*   Updated: 2024/01/19 12:55:03 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_free_arrays(char *array[])
{
	int	counter;

	counter = 0;
	while (array[counter])
		free(array[counter++]);
	free(array);
	return (-1);
}

void	ft_error_msg(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	*ft_find_path(char *cmd, char *envp[])
{
	char	**full_path;
	char	*tmp;
	char	*path;
	int		counter;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	while (!ft_strnstr(*envp, "PATH", 4))
		envp++;
	full_path = ft_split(*envp + 5, ':');
	counter = 0;
	while (full_path[counter])
	{
		tmp = ft_strjoin(full_path[counter++], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_arrays(full_path);
			return (path);
		}
		free(path);
	}
	ft_free_arrays(full_path);
	return (NULL);
}

void	ft_execute_cmd(char *argv, t_minishell *shell, char *envp[])
{
	char	**cmd;
	char	*path;

	cmd = ft_split_except(argv, ' ');
	if (!execute_builtin(cmd, shell))
	{
		path = ft_find_path(cmd[0], envp);
		if (!path || (access(path, F_OK | X_OK) != 0 && ft_strchr(cmd[0], '/')))
		{
			perror(cmd[0]);
			ft_free_arrays(cmd);
			exit(EXIT_FAILURE);
		}
		execve(path, cmd, envp);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		ft_free_arrays(cmd);
		exit(EXIT_FAILURE);
	}
}
