/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:36:48 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/01 15:35:21 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	shell;
	t_envp		*home_env_test;

	(void)argc;
	(void)argv;
	print_envp(envp);
	init_shell(&shell, envp);
	print_env_list(shell.l_envp);
	home_env_test = get_env_var("HOME", shell.l_envp);
	if (home_env_test != NULL)
		ft_printf("Teste HOME: %s\n", home_env_test->value);
	else
		ft_printf("Teste HOME falhou, variável não encontrada.\n");
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
