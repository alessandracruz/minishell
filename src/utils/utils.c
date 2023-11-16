/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:53:35 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/15 22:20:00 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*get_env_var(const char *name, t_envp *env_list)
{
	while (env_list != NULL)
	{
		if (strcmp(env_list->name, name) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	update_env_var(const char *name, const char *value, t_envp **env_list)
{
	t_envp	*env_var;
	t_envp	*new_var;

	env_var = get_env_var(name, *env_list);
	if (env_var != NULL)
	{
		free(env_var->value);
		env_var->value = strdup(value);
	}
	else
	{
		new_var = malloc(sizeof(t_envp));
		new_var->name = strdup(name);
		new_var->value = strdup(value);
		new_var->next = *env_list;
		*env_list = new_var;
	}
}

void	add_env_var(t_envp **env_list, const char *name, const char *value)
{
	t_envp	*new_var;

	new_var = malloc(sizeof(t_envp));
	if (!new_var)
		return ;
	new_var->name = strdup(name);
	if (!new_var->name)
	{
		free(new_var);
		return ;
	}
	new_var->value = strdup(value);
	if (!new_var->value)
	{
		free(new_var->name);
		free(new_var);
		return ;
	}
	new_var->next = *env_list;
	*env_list = new_var;
}

void	print_env_list(t_envp *env_list)
{
	t_envp	*current;

	current = env_list;
	while (current != NULL)
	{
		printf("%s = %s\n", current->name, current->value);
		current = current->next;
	}
}
