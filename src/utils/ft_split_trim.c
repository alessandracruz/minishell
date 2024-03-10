/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_trim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:41:41 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/10 17:36:47 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**free_arrays_return(char **pointer)
{
	ft_free_arrays(pointer);
	return (NULL);
}

static int	ft_how_many_splits(char const *s, char *c)
{
	int	split;
	int	counter;

	split = 0;
	counter = -1;
	while (s[++counter])
	{
		if (ft_is_quote(s[counter]) && ft_check_quote(s + counter))
		{
			if (!counter || ft_strchr(c, s[counter - 1]))
				split++;
			counter += ft_check_quote(s + counter);
		}
		else if (!ft_strchr(c, s[counter]) && (!counter
				|| ft_strchr(c, s[counter - 1])))
			split++;
	}
	return (split);
}

static char	*ft_put_string_loop(char const *s, int *start, int *size, char *c)
{
	while (s[*start + *size] != '\0' && (!ft_strchr(c, s[*start + *size])
			|| ft_check_inside_quotes(s, *start + *size) != -1))
	{
		if (ft_is_quote(s[*size]) && ft_check_quote(s + *size) > 0)
			*size += ft_check_quote(s + *size) + 1;
		else
			(*size)++;
	}
	return (ft_substr(s, *start, *size));
}

static int	ft_put_string(char **pointer, char const *s, char *c, char *set)
{
	char	*temp;
	int		start;
	int		size;

	start = 0;
	size = 0;
	while (ft_strchr(c, s[start]) && s[start])
		start++;
	if (!s[start])
		return (start);
	temp = ft_put_string_loop(s, &start, &size, c);
	if (!temp)
		return (-1);
	*pointer = ft_strtrim(temp, set);
	free(temp);
	if (!*pointer)
		return (-1);
	return (start + size);
}

char	**ft_split_trim(char const *s, char *c, char *set)
{
	char	**pointer;
	int		counter;
	int		split;
	int		max;

	if (!s)
		return (NULL);
	split = -1;
	max = ft_how_many_splits(s, c);
	pointer = malloc((max + 1) * sizeof(char *));
	if (!pointer)
		return (NULL);
	while (++split < max && *s)
	{
		counter = ft_put_string(&pointer[split], s, c, set);
		if (counter == -1)
			return (free_arrays_return(pointer));
		s += counter;
	}
	pointer[split] = NULL;
	return (pointer);
}
