/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:20:43 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/01 12:19:13 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*error;
	int		exit_status;

	cmd = ft_split_except(argv, ' ');
	if (!execute_builtin(cmd, shell))
	{
		path = ft_find_path(cmd[0], envp);
		if (!path || (access(path, F_OK | X_OK) != 0 && ft_strchr(cmd[0], '/')))
		{
			error = strerror(errno);
			if (ft_strnstr(error, "denied", ft_strlen(error)))
				exit_status = EXIT_DENIED;
			else
				exit_status = EXIT_NOTFOUND;
			cmd_print_error(cmd[0], error);
			ft_free_arrays(cmd);
			exit(exit_status);
		}
		execve(path, cmd, envp);
		perror(cmd[0]);
		ft_free_arrays(cmd);
		exit(EXIT_NOTFOUND);
	}
	exit(EXIT_SUCCESS);
}
