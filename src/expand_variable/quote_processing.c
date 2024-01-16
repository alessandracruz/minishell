/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:08:56 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/16 10:04:04 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_single_quote(char *arg, int *index)
{
	char	*result;
	int		start;
	int		i;

	start = *index + 1;
	i = start;
	while (arg[i] && arg[i] != '\'')
		i++;
	if (arg[i] == '\'')
	{
		result = ft_substr(arg, start, i - start);
		*index = i + 1;
	}
	else
	{
		print_error("Single quotes not closed", NULL);
		result = NULL;
	}
	return (result);
}

char	*process_double_quote_end(char *arg, char *result, int *index,
		int start)
{
	char	*temp;

	if (arg[*index] == '\"')
	{
		temp = result;
		result = ft_strjoin(result, ft_substr(arg, start, *index - start));
		free(temp);
		*index = *index + 1;
	}
	else
	{
		print_error("Double quotes not closed", NULL);
		free(result);
		result = NULL;
	}
	return (result);
}

char	*process_double_quotes(char *arg, t_minishell *shell, int *index)
{
	int		start;
	int		i;
	char	*result;
	char	*expanded;

	start = *index + 1;
	i = start;
	result = NULL;
	while (arg[i] && arg[i] != '\"')
	{
		if (arg[i] == '$')
		{
			expanded = expand_variable_in_quotes(arg, shell, &i);
			if (!expanded)
			{
				print_error("Variable expansion error", NULL);
				free(result);
				return (NULL);
			}
			result = join_string_and_free(result, expanded);
		}
		else
			i++;
	}
	return (process_double_quote_end(arg, result, index, start));
}

char	*process_quotes(char *arg, t_minishell *shell)
{
	char	*result;
	char	*temp;
	int		i;

	result = NULL;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			temp = process_single_quote(arg, &i);
			result = join_string_and_free(result, temp);
		}
		else if (arg[i] == '\"')
		{
			temp = process_double_quotes(arg, shell, &i);
			result = join_string_and_free(result, temp);
		}
		else
		{
			result = add_char_to_result(result, arg[i]);
			i++;
		}
	}
	return (result);
}
