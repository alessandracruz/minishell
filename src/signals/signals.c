/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:06:20 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/29 11:45:24 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void handle_sigint(int sig)
{
    (void)sig;
	write(1, "\n", 1);
    rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	run_sigint(void)
{
	signal(SIGINT, handle_sigint);
}