/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:17:55 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/01 15:16:15 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(const char *path)
{
	if (chdir(path) == -1)
		print_error("cd error", strerror(errno));
}

void	update_pwd_oldpwd(t_minishell *shell, char *old_dir)
{
	char	new_dir[MAX_PATH_LENGHT];

	if (getcwd(new_dir, sizeof(new_dir)) != NULL)
	{
		update_env_var("PWD", new_dir, &(shell->l_envp));
		update_env_var("OLDPWD", old_dir, &(shell->l_envp));
	}
	else
		perror("cd error: Error receiving current directory");
}

bool	ft_cd(char **args, t_minishell *shell)
{
	char	old_dir[MAX_PATH_LENGHT];
	char   *path_expanded;

	if (getcwd(old_dir, sizeof(old_dir)) == NULL)
	{
		perror("cd error: Error retrieving current directory");
		return (true);
	}
	if (args[1] == NULL || args[1][0] == '\0' || ft_strcmp(args[1], "~") == 0)
		handle_home_directory(shell);
	else if (ft_strcmp(args[1], "-") == 0)
		handle_oldpwd_directory(shell);
	else
	{
		path_expanded = expand_tilde(args[1], shell);
		change_directory(path_expanded);
		free(path_expanded);
	}
	update_pwd_oldpwd(shell, old_dir);
	return (true);
}
