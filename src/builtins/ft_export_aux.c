/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:27:18 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/04 15:37:35 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_var_name(char *name)
{
	if (!ft_isalpha(*name) && *name != '_' && *name != '$')
		return (false);
	name++;
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}

char	*handle_export_quotes(char **arg, char **name, char **value)
{
	int		i;
	char	*temp;
	char	*new_value;
	char	**export;

	export = ft_split_quotes(*value);
	free(*value);
	i = -1;
	while (export[++i])
	{
		if (!i)
			new_value = ft_strdup(export[i]);
		else
		{
			temp = new_value;
			new_value = ft_strjoin(new_value, export[i]);
			free(temp);
		}
	}
	temp = *arg;
	*arg = ft_strjoin(*name, new_value);
	free(new_value);
	double_free(temp, *name);
	free_arguments(export);
	return (ft_strchr(*arg, '='));
}
