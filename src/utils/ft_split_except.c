/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_except.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:20:48 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/03 20:51:29 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_how_many_splits(char const *s, char c)
{
	int	split;
	int	counter;

	split = 0;
	counter = -1;
	while (s[++counter])
	{
		if ((s[counter] == 34 || s[counter] == 39)
			&& ft_check_quote(s + counter))
		{
			if (!counter || s[counter - 1] == c)
				split++;
			counter += ft_check_quote(s + counter);
		}
		else if (s[counter] != c && (!counter || s[counter - 1] == c))
			split++;
	}
	return (split);
}

static int	ft_put_string(char **pointer, int split, char const *s, char c)
{
	int	size;

	size = 0;
	while (s[size] != '\0' && s[size] != c)
	{
		if ((s[size] == 34 || s[size] == 39) && ft_check_quote(s + size) > 0)
			size += ft_check_quote(s + size) + 1;
		else
			size++;
	}
	pointer[split] = ft_substr(s, 0, size);
	if (!pointer[split])
		return (ft_free_arrays(pointer));
	return (size);
}

char	**ft_split_except(char const *s, char c)
{
	char	**pointer;
	int		counter;
	int		split;
	int		max;

	split = 0;
	max = ft_how_many_splits(s, c);
	pointer = malloc((max + 1) * sizeof(char *));
	if (!pointer)
		return (NULL);
	while (split < max && *s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			counter = ft_put_string(pointer, split, s, c);
			if (counter == -1)
				return (NULL);
			s += counter;
			split++;
		}
	}
	pointer[split] = NULL;
	return (pointer);
}
