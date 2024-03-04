/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:35:16 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/03 22:36:56 by matlopes         ###   ########.fr       */
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
		if (ft_check_inside_quotes(input,
				ft_strlen(input) - ft_strlen(temp)) != -1)
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
	t_get_file	get;
	char		*file;
	int			redirects;

	get.check = 0;
	get.index = -1;
	get.counter = -1;
	redirects = get_redirect_amount('<', input);
	if (redirects <= 1)
		execute->current = -1;
	else
		execute->current = redirects - 2;
	while (ft_strchr(input + ++get.counter, '<'))
	{
		get.temp = ft_strchr(input + get.counter, '<');
		if (ft_check_inside_quotes(input,
				ft_strlen(input) - ft_strlen(get.temp)) != -1)
			get.counter = (ft_strlen(input) - ft_strlen(get.temp)) + 1;
		else
		{
			get.counter = ft_strlen(input) - ft_strlen(get.temp);
			get.temp = execute->cmds[++get.index];
			file = ft_substr(get.temp, 0, ft_strlen(get.temp)
					- ft_strlen(ft_strchr(get.temp, ' ')));
			get.fd = open(file, O_RDONLY);
			if (get.fd == -1)
				return (print_error(file, strerror(errno)));
			if (get.check++)
				close(execute->fd_files[0]);
			execute->fd_files[0] = get.fd;
			execute->cmds[get.index] = ft_substr(get.temp, ft_strlen(file) + 1,
					ft_strlen(get.temp) - (ft_strlen(file) + 1));
			double_free(get.temp, file);
		}
	}
	return (0);
}

int	get_fileout(char *input, t_execute *execute)
{
	t_get_file	get;

	get.check = 0;
	get.index = -1;
	get.counter = -1;
	execute->amount -= get_redirect_amount('>', input);
	while (ft_strchr(input + ++get.counter, '>'))
	{
		get.temp = ft_strchr(input + get.counter, '>');
		if (ft_check_inside_quotes(input, ft_strlen(input)
				- ft_strlen(get.temp)) != -1)
			get.counter = (ft_strlen(input) - ft_strlen(get.temp)) + 2;
		else
		{
			get.counter = ft_strlen(input) - ft_strlen(get.temp);
			if (get.temp[1] == '>')
			{
				get.counter++;
				get.fd = open(execute->cmds[execute->amount + ++get.index],
						O_CREAT | O_RDWR | O_APPEND, 00700);
			}
			else
				get.fd = open(execute->cmds[execute->amount + ++get.index],
						O_CREAT | O_RDWR | O_TRUNC, 00700);
			if (get.fd == -1)
			{
				print_error(execute->cmds[execute->amount + get.index],
					strerror(errno));
				return (-1);
			}
			if (get.check++)
				close(execute->fd_files[1]);
			execute->fd_files[1] = get.fd;
		}
	}
	return (0);
}