/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:35:16 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/08 14:01:12 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filein(t_cmd *cmd, int index, t_minishell *shell)
{
	int		fd;
	int		start;
	int		check;
	char	*file;
	int		counter;
	char	*pointer;

	counter = 1;
	check = 0;
	pointer = ft_strchr(cmd->cmd + index, '<');
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
	
	file = ft_substr(pointer, (start + check),(counter - start) - check);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		shell->redirect_exit = EXIT_FAILURE;
		print_error(file, strerror(errno));
		return (NULL);
	}
	if (cmd->fd[0] != 0)
		close(cmd->fd[0]);
	cmd->fd[0] = fd;
	return (ft_cutstr(cmd->cmd, (ft_strlen(cmd->cmd) - ft_strlen(pointer)),
			(counter + check)));
}

char	*fileout(t_cmd *cmd, int index, t_minishell *shell)
{
	int		fd;
	int		start;
	int		check;
	char	*file;
	int		counter;
	char	*pointer;

	counter = 1;
	check = 0;
	pointer = ft_strchr(cmd->cmd + index, '>');
	while (pointer[counter] && pointer[counter] == ' ')
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
	
	file = ft_substr(pointer, (start + check),(counter - start) - check);
	if (pointer[1] == '>')
		{
			counter++;
			fd = open(file, O_CREAT | O_RDWR | O_APPEND, 00700);
		}
		else
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 00700);
	if (fd == -1)
	{
		shell->redirect_exit = EXIT_FAILURE;
		print_error(file, strerror(errno));
		return (NULL);
	}
	if (cmd->fd[1] != 1)
		close(cmd->fd[1]);
	cmd->fd[1] = fd;
	return (ft_cutstr(cmd->cmd, (ft_strlen(cmd->cmd) - ft_strlen(pointer)),
			(counter + check)));
}