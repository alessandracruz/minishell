/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:20:48 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/04 14:50:27 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_how_many_splits(char const *s)
{
	int	split;
	int	counter;

	split = 1;
	counter = -1;
	while (s[++counter])
	{
		if (ft_is_quote(s[counter]) && ft_check_quote(s + counter))
		{
			if (counter && ft_check_quote(s + counter) < (int)ft_strlen(s) - 1)
				split++;
			if (!counter && ft_check_quote(s + counter) < (int)ft_strlen(s) - 1)
				split++;
			counter += ft_check_quote(s + counter);
		}
	}
	return (split);
}

static int	ft_put_string(char **pointer, int split, char const *s)
{
	int	size;
	int	start;

	size = 0;
	start = 0;
	while (s[size] != '\0')
	{
		if (ft_is_quote(s[size]) && ft_check_quote(s + size) > 0 && size)
			break ;
		else if (ft_is_quote(s[size]) && ft_check_quote(s + size) > 0)
		{
			start = 1;
			size += ft_check_quote(s + size) + 1;
			break ;
		}
		size++;
	}
	pointer[split] = ft_substr(s, start, size - (start * 2));
	if (!pointer[split])
		return (ft_free_arrays(pointer));
	return (size);
}

char	**ft_split_quotes(char const *s)
{
	char	**pointer;
	int		counter;
	int		split;
	int		max;

	split = 0;
	max = ft_how_many_splits(s);
	pointer = malloc((max + 1) * sizeof(char *));
	if (!pointer)
		return (NULL);
	while (split < max && *s)
	{
		counter = ft_put_string(pointer, split, s);
		if (counter == -1)
			return (NULL);
		s += counter;
		split++;
	}
	pointer[split] = NULL;
	return (pointer);
}
