/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:17:55 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/16 12:02:08 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(const char *path)
{
	if (chdir(path) == -1)
		print_error("cd error:", strerror(errno));
}

void	handle_home_directory(t_minishell *shell)
{
	t_envp	*home_env;

	home_env = get_env_var("HOME", shell->l_envp);
	if (home_env == NULL || home_env->value == NULL)
		print_error("cd error: HOME not set", NULL);
	else
		change_directory(home_env->value);
}

void	handle_oldpwd_directory(t_minishell *shell)
{
	t_envp	*oldpwd_env;

	oldpwd_env = get_env_var("OLDPWD", shell->l_envp);
	if (oldpwd_env == NULL || oldpwd_env->value == NULL)
		print_error("cd: OLDPWD not set", NULL);
	else
	{
		ft_printf("%s\n", oldpwd_env->value);
		change_directory(oldpwd_env->value);
	}
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

	if (getcwd(old_dir, sizeof(old_dir)) == NULL)
	{
		perror("cd error: Error retrieving current directory");
		return (true);
	}
	if (args[1] == NULL || args[1][0] == '\0')
		handle_home_directory(shell);
	else if (strcmp(args[1], "-") == 0)
		handle_oldpwd_directory(shell);
	else
		change_directory(args[1]);
	return (true);
}
