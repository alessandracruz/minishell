/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:49:55 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/03 15:10:53 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_inputs(char *eof, t_execute *execute, t_minishell *shell)
{
	pid_t	pid;
	int		fd[2];
	char	*tmp;
	char	*line;
	int		status;

	pipe(fd);
	if (execute->fd_files[0] != 0)
		close(execute->fd_files[0]);
	execute->fd_files[0] = fd[0];
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		signal(SIGINT, sig_new_line);
		signal(SIGILL, sig_heredoc_break);
		while (true)
		{
			tmp = readline("> ");
			line = ft_strjoin(tmp, "\n");
			if (!ft_strcmp(eof, tmp))
				break ;
			write(fd[1], line, ft_strlen(line));
			free(tmp);
			free(line);
		}
		free(eof);
		free(tmp);
		free(line);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	shell->heredoc_exit = WEXITSTATUS(status);
	close(fd[1]);
}

char	*heredoc(char *input, int index, t_execute *execute, t_minishell *shell)
{
	char	*eof;
	char	*pointer;
	int		start;
	int		counter;
	int		check;

	counter = 2;
	check = 0;
	pointer = ft_strnstr(input + index, "<<", ft_strlen(input));
	while (pointer[counter] == ' ')
		counter++;
	start = counter;
	if ((pointer[counter] == 34 || pointer[counter] == 39)
		&& ft_check_quote(pointer + counter))
	{
		check = 1;
		counter += ft_check_quote(pointer + counter);
	}
	else
		while (pointer[counter] && pointer[counter] != ' ')
			counter++;
	eof = ft_substr(pointer, (start + check), (counter - start) - check);
	heredoc_inputs(eof, execute, shell);
	free(eof);
	if (shell->heredoc_exit)
		return (NULL);
	return (ft_cutstr(input, (ft_strlen(input) - ft_strlen(pointer)),
			(counter + check)));
}
