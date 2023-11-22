/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:36:14 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/22 11:26:15 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quotes(char *arg, t_minishell *shell)
{
	char	*result;
	int		i;
	char	current_char[2];
	char	*temp;

	result = ft_strdup("");
	i = 0;
	while (arg[i])
	{
		temp = result;
		if (arg[i] == '\'')
			result = process_single_quote(arg, &i);
		else if (arg[i] == '\"')
			result = process_double_quotes(arg, shell, &i);
		else
		{
			current_char[0] = arg[i];
			current_char[1] = '\0';
			result = ft_strjoin(result, current_char);
			free(temp);
			i++;
		}
	}
	return (result);
}
