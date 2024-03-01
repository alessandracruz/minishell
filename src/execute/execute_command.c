/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:41:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/01 14:27:14 by matlopes         ###   ########.fr       */
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
	char	*temp;
	int		fd;
	int		check;
	int		index;
	int		counter;

	counter = -1;
	index = 0;
	while (ft_strchr(input + ++counter, '>'))
	{
		temp = ft_strchr(input + counter, '>');
		counter = ft_strlen(input) - ft_strlen(temp);
		if (temp[1] == '>')
			counter++;
		index++;
	}
	execute->amount -= index;
	index = -1;
	check = 0;
	counter = -1;
	while (ft_strchr(input + ++counter, '>'))
	{
		temp = ft_strchr(input + counter, '>');
		counter = ft_strlen(input) - ft_strlen(temp);
		if (temp[1] == '>')
		{
			counter++;	
			fd = open(execute->cmds[execute->amount + ++index],
					O_CREAT | O_RDWR | O_APPEND, 00700);
		}
		else
			fd = open(execute->cmds[execute->amount + ++index],
					O_CREAT | O_RDWR | O_TRUNC, 00700);
		if (fd == -1)
		{
			print_error(execute->cmds[execute->amount + index], strerror(errno));
			return (-1);
		}
		if (check++)
			close(execute->fd_files[1]);
		execute->fd_files[1] = fd;
	}
	return (0);
}

int	get_cmds(char **input, t_execute *execute, t_minishell *shell)
{
	char	*temp;

	execute->fd_files[0] = 0;
	execute->fd_files[1] = 1;
	while (ft_strnstr(*input, "<<", ft_strlen(*input)))
	{
		temp = heredoc(*input, execute, shell);
		shell->exit = shell->heredoc_exit;
		if (!temp)
			return (-1);
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
	free_arguments(execute->cmds);
	fd_dup_close(execute->fd_files[0], 0);
	fd_dup_close(execute->fd_files[1], 1);
	execute_builtin(cmd, shell);
	free_arguments(cmd);
	dup2(saved_stds[0], 0);
	dup2(saved_stds[1], 1);
	shell->exit = EXIT_SUCCESS;
}

void	execute_command(char **input, t_minishell *shell, char **envp)
{
	t_execute	execute;
	int			pid;
	int			status;

	shell->heredoc_exit = EXIT_SUCCESS;
	signal(SIGINT, sig_empty);
	if (get_cmds(input, &execute, shell) == -1)
		return ;
	if (execute.amount == 1 && is_builtin(execute.cmds[execute.amount - 1]))
		return (execute_single_builtin(&execute, shell));
	shell->exit = EXIT_SUCCESS;
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, sig_new_line);
		ft_pipex(&execute, shell, envp);
		free_arguments(execute.cmds);
		exit(shell->exit);
	}
	waitpid(pid, &status, 0);
	shell->exit = WEXITSTATUS(status);
	free_arguments(execute.cmds);
}
