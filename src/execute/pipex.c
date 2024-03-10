/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:52:51 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/10 17:54:03 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex_wait(t_execute *execute, t_minishell *shell)
{
	int	status;
	int	counter;

	counter = -1;
	while (++counter < execute->amount)
	{
		waitpid(execute->pids[counter], &status, 0);
		shell->exit = WEXITSTATUS(status);
	}
	free(execute->pids);
}

void	pipex_execute(t_cmd *cmd, t_execute *execute, t_minishell *shell)
{
	execute->pids[cmd->index] = fork();
	if (!execute->pids[cmd->index])
	{
		close(execute->fds[0]);
		if (cmd->fd[0] != 0)
			close(cmd->fd[0]);
		if (cmd->fd[1] != 1 || !cmd->next)
			fd_dup_close(cmd->fd[1], 1);
		else
			fd_dup_close(execute->fds[1], 1);
		ft_execute_cmd(cmd->cmd, execute, shell);
	}
	else
	{
		if (!cmd->next && cmd->fd[1] != 1)
			close(cmd->fd[1]);
		close(execute->fds[1]);
	}
}

void	ft_pipex_loop(t_cmd *cmd, t_execute *execute, t_minishell *shell)
{
	while (++execute->current < execute->amount)
	{
		pipe(execute->fds);
		pipex_execute(cmd, execute, shell);
		if (cmd->next && cmd->next->fd[0] != 0)
		{
			close(execute->fds[0]);
			fd_dup_close(cmd->next->fd[0], 0);
		}
		else if (cmd->next && cmd->fd[1] != 1)
		{
			close(execute->fds[0]);
			fd_dup_close(cmd->fd[1], 0);
		}
		else
			fd_dup_close(execute->fds[0], 0);
		cmd = cmd->next;
	}
}

void	ft_pipex(t_execute *execute, t_minishell *shell)
{
	t_cmd	*cmd;

	cmd = execute->cmds;
	execute->pids = malloc(sizeof(pid_t) * (execute->amount));
	if (!execute->pids)
		exit(EXIT_FAILURE);
	fd_dup_close(cmd->fd[0], 0);
	execute->current = -1;
	ft_pipex_loop(cmd, execute, shell);
	pipex_wait(execute, shell);
}
