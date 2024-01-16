/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:41:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/16 16:42:38 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_external_command(char **arguments)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(arguments[0], arguments) == -1)
		{
			print_error("Error executing command", NULL);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		print_error("Error forking process", NULL);
}

void	free_arguments(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
	{
		free(arguments[i]);
		i++;
	}
	free(arguments);
}

void	execute_command(char *input, t_minishell *shell)
{
	char	**arguments;

	arguments = ft_split_except(input, ' ');
	if (arguments[0] == NULL)
	{
		free_arguments(arguments);
		return ;
	}
	if (execute_builtin(arguments, shell))
	{
		free_arguments(arguments);
		return ;
	}
	execute_external_command(arguments);
	free_arguments(arguments);
}
