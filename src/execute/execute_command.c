/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:41:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/06 08:04:24 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmds_each(char **input, t_execute *execute, t_minishell *shell)
{
	char	*temp;
	int		counter;

	counter = 0;
	while (ft_strnstr(*input + counter, "<<", ft_strlen(*input) - counter))
	{
		temp = ft_strnstr(*input + counter, "<<", ft_strlen(*input) - counter);
		if (ft_check_inside_quotes(*input,
				ft_strlen(*input) - ft_strlen(temp)) != -1)
			counter = (ft_strlen(*input) - ft_strlen(temp)) + 2;
		else
		{
			temp = heredoc(*input, counter, execute, shell);
			shell->exit = shell->heredoc_exit;
			if (!temp)
				return (-1);
			free(*input);
			*input = temp;
			counter = 0;
		}
	}
	return (0);
}

int	get_cmds(char **input, t_execute *execute, t_minishell *shell)
{
	execute->fd_files[0] = 0;
	execute->fd_files[1] = 1;
	if (get_cmds_each(input, execute, shell) == -1)
		return (-1);
	execute->cmds = ft_split_trim(*input, "<|>", " ");
	if (execute->cmds[0] == NULL)
		return (ft_free_arrays(execute->cmds));
	execute->amount = arguments_counter(execute->cmds);
	if (!get_filein(*input, execute, shell)
		|| !get_fileout(*input, execute, shell))
		return (ft_free_arrays(execute->cmds));
	return (0);
}

void	execute_single_builtin(t_execute *execute, t_minishell *shell)
{
	char		**cmd;
	int			saved_stds[2];

	shell->builtin_exit = EXIT_SUCCESS;
	saved_stds[0] = dup(0);
	saved_stds[1] = dup(1);
	cmd = ft_split_except(execute->cmds[execute->amount - 1], ' ');
	free_arguments(execute->cmds);
	fd_dup_close(execute->fd_files[0], 0);
	fd_dup_close(execute->fd_files[1], 1);
	execute_builtin(cmd, shell);
	free_arguments(cmd);
	dup2(saved_stds[0], 0);
	dup2(saved_stds[1], 1);
	if (shell->builtin_exit != EXIT_SUCCESS)
		shell->exit = shell->builtin_exit;
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
		free_arguments(execute->cmds);
		exit(shell->exit);
	}
	waitpid(pid, &status, 0);
	shell->exit = WEXITSTATUS(status);
	free_arguments(execute->cmds);
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
	if (execute.amount == 1 && is_builtin(execute.cmds[execute.amount - 1]))
		return (execute_single_builtin(&execute, shell));
	shell->exit = EXIT_SUCCESS;
	execute_command_fork(input, &execute, shell);
}
