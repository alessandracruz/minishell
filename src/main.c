/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:36:48 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/01 18:38:37 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (TRUE)
	{
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
		execute_command(&input, &shell, envp);
		free(input);
	}
	free_memory(&shell);
	return (0);
}
