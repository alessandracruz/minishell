/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:37:21 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/01 12:31:50 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_new_line(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
    exit(EXIT_FORK);
}

void	sig_heredoc_break(int sig)
{
	(void)sig;
	exit(EXIT_FORK);
}

void	sig_empty(int sig)
{
	(void)sig;
}

