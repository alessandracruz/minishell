/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:23:05 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/17 00:03:16 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *var_name, t_minishell *shell)
{
	t_envp	*env_var;

	env_var = get_env_var(var_name, shell->l_envp);
	if (env_var && env_var->value)
		return (ft_strdup(env_var->value));
	else
		return (ft_strdup(""));
}

char	*expand_variable_in_quotes(char *arg,
		t_minishell *shell, int *index)
{
	char	*var_name;
	char	*var_value;
	char	*result;
	int		start;

	if (arg[*index] != '$')
		return (ft_strdup(""));
	start = *index + 1;
	(*index)++;
	while (arg[*index] && (ft_isalnum(arg[*index]) || arg[*index] == '-'))
		(*index)++;
	var_name = ft_substr(arg, start, *index - start);
	var_value = get_variable_value(var_name, shell);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	result = ft_strdup(var_value);
	free(var_value);
	return (result);
}
