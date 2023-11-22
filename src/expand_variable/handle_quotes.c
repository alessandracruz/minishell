/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:36:14 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/21 18:15:18 by acastilh         ###   ########.fr       */
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
		print_error("Single quotes not closed");
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
		print_error("Double quotes not closed");
		free(result);
		result = NULL;
	}
	return (result);
}

char	*join_string_and_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new_str);
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
				print_error("Variable expansion error");
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
