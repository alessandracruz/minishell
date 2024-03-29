/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:49:55 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/06 10:33:34 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_inputs(char *eof, int fd[])
{
	char	*tmp;
	char	*line;

	close(fd[0]);
	signal(SIGINT, sig_new_line);
	signal(SIGILL, sig_heredoc_break);
	while (true)
	{
		tmp = readline("> ");
		line = ft_strjoin(tmp, "\n");
		if (!tmp || !ft_strcmp(eof, tmp))
			break ;
		write(fd[1], line, ft_strlen(line));
		double_free(tmp, line);
	}
	free(eof);
	double_free(tmp, line);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

void	heredoc_init_inputs(char *eof, t_cmd *cmd, t_minishell *shell)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	if (cmd->fd[0] != 0)
		close(cmd->fd[0]);
	cmd->fd[0] = fd[0];
	pid = fork();
	if (!pid)
		heredoc_inputs(eof, fd);
	waitpid(pid, &status, 0);
	shell->heredoc_exit = WEXITSTATUS(status);
	close(fd[1]);
	free(eof);
}

char	*heredoc(t_cmd *cmd, int index, t_minishell *shell)
{
	char	*pointer;
	int		start;
	int		counter;
	int		check;

	counter = 2;
	check = 0;
	pointer = ft_strnstr(cmd->cmd + index, "<<", ft_strlen(cmd->cmd));
	while (pointer[counter] == ' ')
		counter++;
	start = counter;
	if (ft_is_quote(pointer[counter]) && ft_check_quote(pointer + counter))
	{
		check = 1;
		counter += ft_check_quote(pointer + counter);
	}
	else
		while (pointer[counter] && pointer[counter] != ' ')
			counter++;
	heredoc_init_inputs(ft_substr(pointer, (start + check),
			(counter - start) - check), cmd, shell);
	if (shell->heredoc_exit)
		return (NULL);
	return (ft_cutstr(cmd->cmd, (ft_strlen(cmd->cmd) - ft_strlen(pointer)),
			(counter + check)));
}
