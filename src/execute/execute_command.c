/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:41:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/03 20:54:49 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirect_amount(char redirect, char *input)
{
	char	*temp;
	int		index;
	int		counter;

	counter = -1;
	index = 0;
	while (ft_strchr(input + ++counter, redirect))
	{
		temp = ft_strchr(input + counter, redirect);
		if (ft_check_inside_quotes(input, ft_strlen(input) - ft_strlen(temp)) != -1)
			counter = (ft_strlen(input) - ft_strlen(temp)) + 2;
		else
		{
			counter = ft_strlen(input) - ft_strlen(temp);
			if (temp[1] == redirect)
				counter++;
			index++;
		}
	}
	return (index);
}

int	get_filein(char *input, t_execute *execute)
{
	int		fd;
	int		redirects;
	int		index;
	int		check;
	char	*temp;
	char	*file;
	int		counter;

	check = 0;
	index = -1;
	counter = -1;
	redirects = get_redirect_amount('<', input);
	if (redirects <= 1)
		execute->current = -1;
	else
		execute->current = redirects - 2;
	while (ft_strchr(input + ++counter, '<'))
	{
		temp = ft_strchr(input + counter, '<');
		if (ft_check_inside_quotes(input, ft_strlen(input) - ft_strlen(temp)) != -1)
			counter = (ft_strlen(input) - ft_strlen(temp)) + 1;
		else
		{
			counter = ft_strlen(input) - ft_strlen(temp);
			temp = execute->cmds[++index];
			file = ft_substr(temp, 0, ft_strlen(temp)
					- ft_strlen(ft_strchr(temp, ' ')));
			fd = open(file, O_RDONLY);
			if (fd == -1)
			{
				print_error(file, strerror(errno));
				return (-1);
			}
			if (check++)
				close(execute->fd_files[0]);
			execute->fd_files[0] = fd;
			execute->cmds[index] = ft_substr(temp, ft_strlen(file) + 1, ft_strlen(temp)
					- (ft_strlen(file) + 1));
			free(temp);
			free(file);
		}
	}
	return (0);
}


int	get_fileout(char *input, t_execute *execute)
{
	int		fd;
	int		check;
	int		index;
	char	*temp;
	int		counter;

	check = 0;
	index = -1;
	counter = -1;
	execute->amount -= get_redirect_amount('>', input);
	while (ft_strchr(input + ++counter, '>'))
	{
		temp = ft_strchr(input + counter, '>');
		if (ft_check_inside_quotes(input, ft_strlen(input) - ft_strlen(temp)) != -1)
			counter = (ft_strlen(input) - ft_strlen(temp)) + 2;
		else
		{
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
				print_error(execute->cmds[execute->amount + index],
					strerror(errno));
				return (-1);
			}
			if (check++)
				close(execute->fd_files[1]);
			execute->fd_files[1] = fd;
		}
	}
	return (0);
}

int	get_cmds(char **input, t_execute *execute, t_minishell *shell)
{
	char	*temp;
	int		counter;

	counter = 0;
	execute->fd_files[0] = 0;
	execute->fd_files[1] = 1;
	while (ft_strnstr(*input + counter, "<<", ft_strlen(*input) - counter))
	{
		temp = ft_strnstr(*input + counter, "<<", ft_strlen(*input) - counter);
		if (ft_check_inside_quotes(*input, ft_strlen(*input) - ft_strlen(temp)) != -1)
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

void	execute_command(char **input, t_minishell *shell)
{
	t_execute	execute;
	int			pid;
	int			status;

	
	shell->heredoc_exit = EXIT_SUCCESS;
	if (g_signal_exit)
		shell->exit = g_signal_exit;
	signal(SIGINT, sig_empty);
	if (get_cmds(input, &execute, shell) == -1)
		return ;
	if (execute.amount == 1 && is_builtin(execute.cmds[execute.amount - 1]))
		return (execute_single_builtin(&execute, shell));
	shell->exit = EXIT_SUCCESS;
	pid = fork();
	if (!pid)
	{
		signal(SIGQUIT, handle_sigquit);
		signal(SIGINT, sig_new_line);
		ft_pipex(&execute, shell);
		free_arguments(execute.cmds);
		exit(shell->exit);
	}
	waitpid(pid, &status, 0);
	shell->exit = WEXITSTATUS(status);
	free_arguments(execute.cmds);
}
