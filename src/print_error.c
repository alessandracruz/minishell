/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:54:29 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/16 16:41:02 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *message, const char *error)
{
	write(STDERR_FILENO, "Erro: ", 6);
	write(STDERR_FILENO, message, ft_strlen(message));
	if (error)
	{
		write(STDERR_FILENO, " ", 1);
		write(STDERR_FILENO, error, ft_strlen(error));
	}
	write(STDERR_FILENO, "\n", 1);
}
