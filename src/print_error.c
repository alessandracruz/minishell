/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:54:29 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/03 22:28:18 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_print_error(const char *message, const char *error)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	if (error)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, error, ft_strlen(error));
	}
	write(STDERR_FILENO, "\n", 1);
}

int	print_error(const char *message, const char *error)
{
	write(STDERR_FILENO, "Erro: ", 6);
	write(STDERR_FILENO, message, ft_strlen(message));
	if (error)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, error, ft_strlen(error));
	}
	write(STDERR_FILENO, "\n", 1);
	return (-1);
}
