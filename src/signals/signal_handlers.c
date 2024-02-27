/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:06:20 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/27 16:49:23 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void handle_sigint(int sig)
{
    (void)sig;
	write(1, "\n", 1);
    rl_on_new_line();        // Prepara para uma nova linha    
	rl_replace_line("", 0);  // Limpa a linha atual
	rl_redisplay();
  //  ft_putstr_fd("\n", 2);  // Apenas imprime uma nova linha
    // Removida a chamada para rl_redisplay()
}

/*
void	handle_sigint(int sig)
{
	printf("1\n");
	if (sig == SIGINT && r_signal.shell_state == SH_CHILD)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (sig == SIGINT && r_signal.shell_state == SH_READ)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGINT && r_signal.shell_state == SH_EXEC)
		return ;
}
*/

void	handle_sigquit(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	handle_sigint_fork(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
}

void	new_line(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}

void	run_signals(void)
{
	signal(SIGINT, handle_sigint);
}

void	stop_signals(void)
{
	signal(SIGINT, new_line);
}