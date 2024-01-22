/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:52:51 by matlopes          #+#    #+#             */
/*   Updated: 2024/01/22 15:01:57 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipex_primary(char *cmd, t_minishell *shell, char *envp[])
{
	int		fd[2];
	pid_t	check;

	pipe(fd);
	check = fork();
	if (check == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		ft_execute_cmd(cmd, shell, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

void	ft_pipex_secondary(char *cmd, t_execute *execute, t_minishell *shell,
	char *envp[])
{
	if (execute->hasFiles[0])
		close(execute->fd_files[0]);
	dup2(execute->fd_files[1], 1);
	if (execute->hasFiles[1])
		close(execute->fd_files[1]);
	ft_execute_cmd(cmd, shell, envp);
	exit(EXIT_SUCCESS);
}

void	ft_pipex(t_execute *execute, t_minishell *shell, char *envp[])
{
	int		counter;
	pid_t	pid;
	pid_t	*child_pids;

	child_pids = malloc(sizeof(pid_t) * (execute->cmds_size));
	counter = execute->hasFiles[0] - 1;
	dup2(execute->fd_files[0], 0);
	while (++counter < execute->cmds_size)
	{
		if (counter < execute->cmds_size - 1)
			ft_pipex_primary(execute->cmds[counter], shell, envp);
		else
		{
			pid = fork();
			if (pid == 0)
				ft_pipex_secondary(execute->cmds[counter], execute, shell,
					envp);
			else if (pid > 0)
				child_pids[counter] = pid;
		}
	}
	counter = execute->hasFiles[0] - 1;
	while (++counter < execute->cmds_size)
		waitpid(child_pids[counter], NULL, 0);
	free(child_pids);
}
