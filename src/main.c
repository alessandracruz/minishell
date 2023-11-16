/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:36:48 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/15 22:07:32 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	signal_number;

signal_number = 0;*/

int	main(int /* argc */, char ** /* argv */, char **envp)
{
	char		*input;
	t_minishell	shell;
	t_envp		*home_env_test;

	print_envp(envp);
	init_shell(&shell, envp);
	print_env_list(shell.l_envp);
	home_env_test = get_env_var("HOME", shell.l_envp);
	if (home_env_test != NULL)
	{
		printf("Teste HOME: %s\n", home_env_test->value);
	}
	else
	{
		printf("Teste HOME falhou, variável não encontrada.\n");
	}
	while (TRUE)
	{
		input = display_prompt();
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		execute_command(input, &shell);
		free(input);
	}
	return (0);
}
