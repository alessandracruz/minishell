/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:52:51 by matlopes          #+#    #+#             */
/*   Updated: 2024/01/19 15:52:39 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipex_primary(char *argv, t_minishell *shell, char *envp[])
{
	int		fd[2];
	pid_t	check;
	pipe(fd);
	check = fork();
	if (check == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		ft_execute_cmd(argv, shell, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

void	ft_pipex_secondary(char *argv, int *fd_files, t_minishell *shell, char *envp[])
{
	if (fd_files[0] != 0)
		close(fd_files[0]);
	dup2(fd_files[1], 1);
	if (fd_files[1] != 1)
		close(fd_files[1]);
	ft_execute_cmd(argv, shell, envp);
}

void	ft_pipex(char *argv[], int argc, int *hasFiles, t_minishell *shell, char *envp[])
{
	int	counter;
	int	fd_files[2];


	fd_files[0] = 0;
	fd_files[1] = 1;
	if (hasFiles[0])
		fd_files[0] = open(argv[0], O_RDONLY);
	if (hasFiles[1])
		fd_files[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 00700);
	counter = hasFiles[0] - 1;
	argc -= hasFiles[1];
	if (fd_files != 0)
		dup2(fd_files[0], 0);
	while (++counter < argc)
	{
		if (counter < argc - 1)
		{
			ft_pipex_primary(argv[counter], shell, envp);
			
		}
		else
			ft_pipex_secondary(argv[counter], fd_files, shell, envp);
	}
	waitpid(-1, NULL, 0);
}