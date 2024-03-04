/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:20:43 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/03 20:49:20 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_string(char *str, char **array)
{
	int	counter;

	counter = 0;
	while (array[counter] && !ft_strnstr(array[counter], str, ft_strlen(str)))
		counter++;
	return (array[counter]);
}

char	*ft_find_path(char *cmd, char *envp[])
{
	char	*pointer;
	char	**full_path;
	char	*tmp;
	char	*path;
	int		counter;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	pointer = ft_find_string("PATH", envp);
	if (!pointer)
		return (NULL);
	full_path = ft_split(pointer + 5, ':');
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

int	ft_check_execute(char **cmd, char *path, char **envp)
{
	char	*error;
	int		check;
	int		exit_status;

	check = 1;
	exit_status = 0;
	if (!ft_strlen(cmd[0]) || !path || (access(path, F_OK | X_OK) != 0
			&& ft_strchr(cmd[0], '/')))
	{
		error = strerror(errno);
		if (ft_strnstr(error, "denied", ft_strlen(error)) || !ft_strlen(cmd[0]))
			exit_status = EXIT_DENIED;
		else if (!path && !ft_find_string("PATH", envp) && ft_strlen(cmd[0]))
		{
			cmd_print_error(cmd[--check], "No such file or directory");
			exit_status = EXIT_NOTFOUND;
		}
		else
			exit_status = EXIT_NOTFOUND;
		if (check)
			cmd_print_error(cmd[0], error);
		ft_free_arrays(envp);
		ft_free_arrays(cmd);
	}
	return (exit_status);
}

void	ft_execute_cmd(char *argv, t_minishell *shell)
{
	char	**cmd;
	char	**envp;
	char	*path;
	int		exit_status;

	cmd = ft_split_except(argv, ' ');
	if (!execute_builtin(cmd, shell))
	{
		envp = get_envp(shell->l_envp);
		path = ft_find_path(cmd[0], envp);
		exit_status = ft_check_execute(cmd, path, envp);
		if (exit_status)
			exit(exit_status);
		execve(path, cmd, envp);
		perror(cmd[0]);
		ft_free_arrays(cmd);
		ft_free_arrays(envp);
		exit(EXIT_NOTFOUND);
	}
	exit(EXIT_SUCCESS);
}
