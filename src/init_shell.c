/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:28:07 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/29 11:58:24 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_from_entry(char *entry, t_envp **env_list)
{
	char	*equal_sign;
	int		name_lenght;
	char	*name;
	char	*value;

	equal_sign = ft_strchr(entry, '=');
	if (equal_sign != NULL)
	{
		name_lenght = equal_sign - entry;
		name = malloc(name_lenght + 1);
		if (name == NULL)
			return ;
		ft_strncpy(name, entry, name_lenght);
		name[name_lenght] = '\0';
		value = ft_strdup(equal_sign + 1);
		if (value == NULL)
		{
			free(name);
			return ;
		}
		if (!add_env_var(env_list, name, value))
		{
			free(name);
			free(value);
		}
		else
		{
			free(name);
			free(value);
		}
	}
}

void	init_shell(t_minishell *shell, char **envp)
{
	int	i;

	i = 0;
	shell->l_envp = NULL;
	shell->current_cmd = NULL;
	shell->exit = EXIT_SUCCESS;
	while (envp[i] != NULL)
	{
		add_env_from_entry(envp[i], &shell->l_envp);
		i++;
	}
}
