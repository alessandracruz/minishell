/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:41:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/19 13:16:48 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	execute_external_command(char **arguments)
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
} */

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

int		arguments_counter(char **argv)
{
	int index;

	index = 0;
	while (argv[index])
		index++;
	return (index);
}

void	execute_command(char *input, t_minishell *shell, char **envp)
{
	char	**argv;
	int		argc;
	int		hasFiles[2];

	hasFiles[0] = 0;
	hasFiles[1] = 0;
	if (ft_strchr(input, '<'))
		hasFiles[0] = 1;
	if (ft_strchr(input, '>'))
		hasFiles[1] = 1;
	argv = ft_split_trim(input, "<|>", " ");
	if (argv[0] == NULL)
		return (free_arguments(argv));
	argc = arguments_counter(argv);
	ft_pipex(argv, argc, hasFiles, shell, envp);
	free_arguments(argv);
}
