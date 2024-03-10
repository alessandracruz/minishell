/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:35:16 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/10 18:16:17 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	filein_open(t_cmd *cmd, t_get_file *get, t_minishell *shell)
{
	get->file = ft_substr(get->pointer, (get->start + get->check),
			(get->counter - get->start) - get->check);
	get->fd = open(get->file, O_RDONLY);
	free(get->file);
	if (get->fd == -1)
	{
		shell->redirect_exit = EXIT_FAILURE;
		print_error(get->file, strerror(errno));
		return (0);
	}
	if (cmd->fd[0] != 0)
		close(cmd->fd[0]);
	cmd->fd[0] = get->fd;
	return (1);
}

char	*filein(t_cmd *cmd, int index, t_minishell *shell)
{
	t_get_file	get;

	get.counter = 1;
	get.check = 0;
	get.pointer = ft_strchr(cmd->cmd + index, '<');
	while (get.pointer[get.counter] == ' ')
		get.counter++;
	get.start = get.counter;
	if (ft_is_quote(get.pointer[get.counter])
		&& ft_check_quote(get.pointer + get.counter))
	{
		get.check = 1;
		get.counter += ft_check_quote(get.pointer + get.counter);
	}
	else
		while (get.pointer[get.counter] && get.pointer[get.counter] != ' ')
			get.counter++;
	if (!filein_open(cmd, &get, shell))
		return (NULL);
	return (ft_cutstr(cmd->cmd, (ft_strlen(cmd->cmd) - ft_strlen(get.pointer)),
			(get.counter + get.check)));
}

int	fileout_open(t_cmd *cmd, t_get_file *get, t_minishell *shell)
{
	get->file = ft_substr(get->pointer, (get->start + get->check),
			(get->counter - get->start) - get->check);
	if (get->pointer[1] == '>')
	{
		get->counter++;
		get->fd = open(get->file, O_CREAT | O_RDWR | O_APPEND, 00700);
	}
	else
		get->fd = open(get->file, O_CREAT | O_RDWR | O_TRUNC, 00700);
	free(get->file);
	if (get->fd == -1)
	{
		shell->redirect_exit = EXIT_FAILURE;
		print_error(get->file, strerror(errno));
		return (0);
	}
	if (cmd->fd[1] != 1)
		close(cmd->fd[1]);
	cmd->fd[1] = get->fd;
	return (1);
}

char	*fileout(t_cmd *cmd, int index, t_minishell *shell)
{
	t_get_file	get;

	get.counter = 1;
	get.check = 0;
	get.pointer = ft_strchr(cmd->cmd + index, '>');
	while (get.pointer[get.counter] && (get.pointer[get.counter] == ' '
			|| get.pointer[get.counter] == '>'))
		get.counter++;
	get.start = get.counter;
	if (ft_is_quote(get.pointer[get.counter])
		&& ft_check_quote(get.pointer + get.counter))
	{
		get.check = 1;
		get.counter += ft_check_quote(get.pointer + get.counter);
	}
	else
		while (get.pointer[get.counter] && get.pointer[get.counter] != ' ')
			get.counter++;
	if (!fileout_open(cmd, &get, shell))
		return (NULL);
	return (ft_cutstr(cmd->cmd, (ft_strlen(cmd->cmd) - ft_strlen(get.pointer)),
			(get.counter + get.check)));
}
