/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:45:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/01 14:51:22 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_home_directory(t_minishell *shell)
{
	t_envp	*home_env;

	home_env = get_env_var("HOME", shell->l_envp);
	if (home_env == NULL || home_env->value == NULL)
		print_error("cd error", "HOME not set");
	else
		change_directory(home_env->value);
}

void	handle_oldpwd_directory(t_minishell *shell)
{
	t_envp	*oldpwd_env;

	oldpwd_env = get_env_var("OLDPWD", shell->l_envp);
	if (oldpwd_env == NULL || oldpwd_env->value == NULL)
		print_error("cd", "OLDPWD not set");
	else
	{
		ft_printf("%s\n", oldpwd_env->value);
		change_directory(oldpwd_env->value);
	}
}

char	*expand_tilde(char *path, t_minishell *shell)
{
	t_envp	*home_env;
	char	*expanded_path;

	if (path[0] == '~')
	{
		home_env = get_env_var("HOME", shell->l_envp);
		if (home_env == NULL || home_env->value == NULL)
		{
			print_error("cd error", "HOME not set");
			return (NULL);
		}
		expanded_path = join_string_and_free(home_env->value, path + 1);
		return (expanded_path);
	}
	return (strdup(path));
}
