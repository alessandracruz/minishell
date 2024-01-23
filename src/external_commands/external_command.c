/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:41:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/22 15:01:35 by matlopes         ###   ########.fr       */
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

int	arguments_counter(char **argv)
{
	int	index;

	index = 0;
	while (argv[index])
		index++;
	return (index);
}

void	execute_command(char *input, t_minishell *shell, char **envp)
{
	t_execute	execute;
	int			check;

	execute.hasFiles[0] = 0;
	execute.hasFiles[1] = 0;
	execute.fd_files[0] = 0;
	execute.fd_files[1] = 1;
	check = fork();
	if (!check)
	{
		execute.cmds = ft_split_trim(input, "<|>", " ");
		if (execute.cmds[0] == NULL)
			return (free_arguments(execute.cmds));
		execute.cmds_size = arguments_counter(execute.cmds);
		if (ft_strchr(input, '<'))
		{
			execute.hasFiles[0] = 1;
			execute.fd_files[0] = open(execute.cmds[0], O_RDONLY);
		}
		if (ft_strchr(input, '>'))
		{
			execute.hasFiles[1] = 1;
			execute.fd_files[1] = open(execute.cmds[--execute.cmds_size],
					O_CREAT | O_RDWR | O_TRUNC, 00700);
		}
		ft_pipex(&execute, shell, envp);
		free_arguments(execute.cmds);
		exit(EXIT_SUCCESS);
	}
	waitpid(-1, NULL, 0);
}
