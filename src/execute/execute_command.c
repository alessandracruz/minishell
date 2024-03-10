/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:41:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/10 17:27:04 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirect_file(t_cmd *cmd, char *temp, int *counter)
{
	if (ft_check_inside_quotes(cmd->cmd,
			ft_strlen(cmd->cmd) - ft_strlen(temp)) != -1)
	{
		*counter = (ft_strlen(cmd->cmd) - ft_strlen(temp)) + 2;
		return (1);
	}
	return (0);
}

int	get_redirect(char *find, char *(*f)(t_cmd*, int, t_minishell*),
	t_cmd *cmd, t_minishell *shell)
{
	char	*temp;
	int		counter;

	counter = 0;
	while (ft_strnstr(cmd->cmd + counter, find, ft_strlen(cmd->cmd) - counter))
	{
		temp = ft_strnstr(cmd->cmd + counter, find,
				ft_strlen(cmd->cmd) - counter);
		if (!get_redirect_file(cmd, temp, &counter))
		{
			temp = (*f)(cmd, counter, shell);
			if (ft_strcmp(find, "<<"))
				shell->exit = shell->heredoc_exit;
			else
				shell->exit = shell->redirect_exit;
			if (!temp)
				return (0);
			free(cmd->cmd);
			cmd->cmd = temp;
			counter = 0;
		}
	}
	return (1);
}

void	execute_single_builtin(t_execute *execute, t_minishell *shell)
{
	char		**cmd;
	int			saved_stds[2];

	shell->builtin_exit = EXIT_SUCCESS;
	saved_stds[0] = dup(0);
	saved_stds[1] = dup(1);
	cmd = ft_split_except(execute->cmds->cmd, ' ');
	free_cmds(&execute->cmds);
	fd_dup_close(execute->cmds->fd[0], 0);
	fd_dup_close(execute->cmds->fd[1], 1);
	execute_builtin(cmd, shell);
	free_arguments(cmd);
	dup2(saved_stds[0], 0);
	dup2(saved_stds[1], 1);
	if (shell->builtin_exit != EXIT_SUCCESS)
		shell->exit = shell->builtin_exit;
	else
		shell->exit = EXIT_SUCCESS;
}

void	execute_command_fork(char **input, t_execute *execute,
	t_minishell *shell)
{
	int			pid;
	int			status;

	pid = fork();
	if (!pid)
	{
		signal(SIGQUIT, handle_sigquit);
		signal(SIGINT, sig_new_line);
		ft_pipex(execute, shell);
		free_cmds(&execute->cmds);
		exit(shell->exit);
	}
	waitpid(pid, &status, 0);
	shell->exit = WEXITSTATUS(status);
	free_cmds(&execute->cmds);
	free(*input);
}

void	execute_command(char **input, t_minishell *shell)
{
	t_execute	execute;

	shell->heredoc_exit = EXIT_SUCCESS;
	if (g_signal_exit)
		shell->exit = g_signal_exit;
	signal(SIGINT, sig_empty);
	if (get_cmds(input, &execute, shell) == -1)
		return ;
	if (execute.amount == 1 && is_builtin(execute.cmds->cmd))
		return (execute_single_builtin(&execute, shell));
	shell->exit = EXIT_SUCCESS;
	execute_command_fork(input, &execute, shell);
}
