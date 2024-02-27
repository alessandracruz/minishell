/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:41:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/27 16:49:38 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_filein(char *input, t_execute *execute)
{
	char	*temp;
	char	*file;

	if (ft_strchr(input, '<'))
	{
		temp = execute->cmds[0];
		file = ft_substr(temp, 0, ft_strlen(temp)
				- ft_strlen(ft_strchr(temp, ' ')));
		execute->fd_files[0] = open(file, O_RDONLY);
		if (execute->fd_files[0] == -1)
		{
			print_error(file, strerror(errno));
			return (-1);
		}
		execute->cmds[0] = ft_substr(temp, ft_strlen(file) + 1, ft_strlen(temp)
				- (ft_strlen(file) + 1));
		free(temp);
	}
	return (0);
}

int	get_fileout(char *input, t_execute *execute)
{
	if (ft_strchr(input, '>'))
	{
		execute->fd_files[1] = open(execute->cmds[--execute->amount],
				O_CREAT | O_RDWR | O_TRUNC, 00700);
		if (execute->fd_files[0] == -1)
		{
			print_error(execute->cmds[--execute->amount], strerror(errno));
			return (-1);
		}
	}
	return (0);
}

int	get_cmds(char **input, t_execute *execute)
{
	char	*temp;

	execute->fd_files[0] = 0;
	execute->fd_files[1] = 1;
	if (ft_strnstr(*input, "<<", ft_strlen(*input)))
	{
		temp = heredoc(*input, execute);
		free(*input);
		*input = temp;
	}
	execute->cmds = ft_split_trim(*input, "<|>", " ");
	if (execute->cmds[0] == NULL)
		return (ft_free_arrays(execute->cmds));
	execute->amount = arguments_counter(execute->cmds);
	if (get_filein(*input, execute) == -1 || get_fileout(*input, execute) == -1)
		return (ft_free_arrays(execute->cmds));
	return (0);
}

void	execute_single_builtin(t_execute *execute, t_minishell *shell)
{
	char		**cmd;
	int			saved_stds[2];

	saved_stds[0] = dup(0);
	saved_stds[1] = dup(1);
	cmd = ft_split_except(execute->cmds[execute->amount - 1], ' ');
	fd_dup_close(execute->fd_files[0], 0);
	fd_dup_close(execute->fd_files[1], 1);
	execute_builtin(cmd, shell);
	free_arguments(cmd);
	dup2(saved_stds[0], 0);
	dup2(saved_stds[1], 1);
}

void	execute_command(char *input, t_minishell *shell, char **envp)
{
	t_execute	execute;
	int			pid;

	if (get_cmds(&input, &execute) == -1)
		return ;
	if (execute.amount == 1 && is_builtin(execute.cmds[execute.amount - 1]))
		return (execute_single_builtin(&execute, shell));
	stop_signals();
	pid = fork();
	if (!pid)
	{
		ft_pipex(&execute, shell, envp);
		free_arguments(execute.cmds);
		exit(EXIT_SUCCESS);
	}
	waitpid(-1, NULL, 0);
}
