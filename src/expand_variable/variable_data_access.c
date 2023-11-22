/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_data_access.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:26:59 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/21 18:00:28 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_name(const char *arg, int start)
{
	int	end;

	end = start;
	while (arg[end] && (ft_isalnum(arg[end]) || arg[end] == '_'))
		end++;
	return (ft_substr(arg, start, end - start));
}

char	*get_variable_value(const char *name, t_minishell *shell)
{
	t_envp	*env_var;

	env_var = get_env_var(name, shell->l_envp);
	if (env_var && env_var->value)
		return (ft_strdup(env_var->value));
	return (ft_strdup(""));
}
