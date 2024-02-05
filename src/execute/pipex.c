/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:52:51 by matlopes          #+#    #+#             */
/*   Updated: 2024/02/05 10:12:11 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex_wait(t_execute *execute)
{
	int	counter;
	int	status;

	counter = -1;
	while (++counter < execute->amount)
		waitpid(execute->pids[counter], &status, 0);
	free(execute->pids);
}

void	pipex_primary(t_execute *execute, t_minishell *shell, char *envp[])
{
	execute->pids[execute->current] = fork();
	if (execute->pids[execute->current] == 0)
	{
		close(execute->fd_files[1]);
		close(execute->fds[0]);
		dup2(execute->fds[1], 1);
		close(execute->fds[1]);
		ft_execute_cmd(execute->cmds[execute->current], shell, envp);
	}
	else
		close(execute->fds[1]);
}

void	pipex_secondary(t_execute *execute, t_minishell *shell, char *envp[])
{
	close(execute->fds[1]);
	execute->pids[execute->current] = fork();
	if (execute->pids[execute->current] == 0)
	{
		close(execute->fds[0]);
		fd_dup_close(execute->fd_files[1], 1);
		ft_execute_cmd(execute->cmds[execute->current], shell, envp);
	}
}

void	ft_pipex(t_execute *execute, t_minishell *shell, char *envp[])
{
	execute->pids = malloc(sizeof(pid_t) * (execute->amount));
	execute->current = -1;
	fd_dup_close(execute->fd_files[0], 0);
	while (++execute->current < execute->amount)
	{
		pipe(execute->fds);
		if (execute->current < execute->amount - 1)
			pipex_primary(execute, shell, envp);
		else
			pipex_secondary(execute, shell, envp);
		dup2(execute->fds[0], 0);
		close(execute->fds[0]);
	}
	pipex_wait(execute);
}
