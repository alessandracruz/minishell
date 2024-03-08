/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:45:06 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/06 13:56:17 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_or_update_env_var(t_minishell *shell, char *name, char *value)
{
	t_envp	*env_var;
	t_envp	*new_var;

	env_var = shell->l_envp;
	while (env_var)
	{
		if (ft_strcmp(env_var->name, name) == 0)
		{
			free(env_var->value);
			env_var->value = ft_strdup(value);
			return (1);
		}
		env_var = env_var->next;
	}
	new_var = (t_envp *)malloc(sizeof(t_envp));
	if (new_var == NULL)
		return (1);
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(value);
	new_var->next = shell->l_envp;
	shell->l_envp = new_var;
	return (1);
}

void	handle_export_argument(t_minishell *shell, char **arg)
{
	char	*name;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(*arg, '=');
	if (equal_sign != NULL)
	{
		if (!equal_sign[1])
		{
			add_or_update_env_var(shell, *arg, "");
			return ;
		}
		name = ft_substr(*arg, 0, ft_strlen(*arg) - ft_strlen(equal_sign) + 1);
		value = ft_substr(*arg, ft_strlen(*arg) - ft_strlen(equal_sign + 1),
				ft_strlen(equal_sign) - 1);
		equal_sign = handle_export_quotes(arg, &name, &value);
		*equal_sign = '\0';
		if (!is_valid_var_name(*arg)
			|| !add_or_update_env_var(shell, *arg, equal_sign + 1))
			ft_printf("export: `%s': not a valid identifier\n",*arg);
	}
	else
	{
		if (!is_valid_var_name(*arg) || !(get_env_var(*arg, shell->l_envp)
				|| add_or_update_env_var(shell, *arg, "")))
			ft_printf("export: `%s': not a valid identifier\n", *arg);
	}
}

void	list_environment_variables(t_minishell *shell)
{
	t_envp	*current;

	current = shell->l_envp;
	while (current != NULL)
	{
		if (current->value != NULL)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
}

bool	ft_export(char **args, t_minishell *shell)
{
	int	i;

	if (args[1] == NULL)
	{
		list_environment_variables(shell);
		return (true);
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (!ft_strchr(args[i], '=') && args[i + 1] && args[i + 1][0] == '=')
		{
			ft_printf("export: `%s': not a valid identifier\n", args[i + 1]);
			return (true);
		}
		handle_export_argument(shell, &args[i]);
		i++;
	}
	return (true);
}
