/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:36:48 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/03 20:54:49 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_exit;

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (TRUE)
	{
		g_signal_exit = 0;
		run_signals();
		input = display_prompt();
		if (input == NULL)
		{
			ft_printf("\n");
			break ;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		execute_command(&input, &shell);
		free(input);
	}
	free_memory(&shell);
	return (0);
}
