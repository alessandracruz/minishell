/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:52:51 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/03 20:49:33 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex_wait(t_execute *execute, t_minishell *shell)
{
	int	status;
	int	counter;

	counter = execute->start - 1;
	while (++counter < execute->amount)
	{
		waitpid(execute->pids[counter - execute->start], &status, 0);
		shell->exit = WEXITSTATUS(status);
	}
	free(execute->pids);
}

void	pipex_primary(t_execute *execute, t_minishell *shell)
{
	execute->pids[execute->current - execute->start] = fork();
	if (execute->pids[execute->current - execute->start] == 0)
	{
		close(execute->fd_files[1]);
		close(execute->fds[0]);
		dup2(execute->fds[1], 1);
		close(execute->fds[1]);
		ft_execute_cmd(execute->cmds[execute->current], shell);
	}
	else
		close(execute->fds[1]);
}

void	pipex_secondary(t_execute *execute, t_minishell *shell)
{
	close(execute->fds[1]);
	execute->pids[execute->current - execute->start] = fork();
	if (execute->pids[execute->current - execute->start] == 0)
	{
		close(execute->fds[0]);
		fd_dup_close(execute->fd_files[1], 1);
		ft_execute_cmd(execute->cmds[execute->current], shell);
	}
}

void	ft_pipex(t_execute *execute, t_minishell *shell)
{
	execute->start = execute->current + 1;
	execute->pids = malloc(sizeof(pid_t) * (execute->amount - execute->start));
	fd_dup_close(execute->fd_files[0], 0);
	while (++execute->current < execute->amount)
	{
		pipe(execute->fds);
		if (execute->current < execute->amount - 1)
			pipex_primary(execute, shell);
		else
			pipex_secondary(execute, shell);
		dup2(execute->fds[0], 0);
		close(execute->fds[0]);
	}
	pipex_wait(execute, shell);
}
