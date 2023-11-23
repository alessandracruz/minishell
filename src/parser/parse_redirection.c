/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:35:57 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/23 00:15:35 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*parse_redirection(char **tokens, int *index)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = ft_strdup(tokens[*index]);
	redir->filename = ft_strdup(tokens[*index + 1]);
	*index = *index + 2;
	return (redir);
}

void	apply_output_redirections(t_cmd_node *cmd)
{
	int	fd;

	if (cmd->output_redirection)
	{
		if (strcmp(cmd->output_redirection->type, ">") == 0)
			fd = open(cmd->output_redirection->filename, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		else if (strcmp(cmd->output_redirection->type, ">>") == 0)
			fd = open(cmd->output_redirection->filename, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open");
			return ;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	apply_simple_input_redirection(t_cmd_node *cmd)
{
	int	fd;

	fd = open(cmd->input_redirection->filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
}

void	apply_here_document(t_cmd_node *cmd)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	line = readline("> ");
	while (line != NULL)
	{
		if (strcmp(line, cmd->input_redirection->filename) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

void	apply_input_redirections(t_cmd_node *cmd)
{
	if (cmd->input_redirection)
	{
		if (strcmp(cmd->input_redirection->type, "<") == 0)
			apply_simple_input_redirection(cmd);
		else if (strcmp(cmd->input_redirection->type, "<<") == 0)
			apply_here_document(cmd);
	}
}
