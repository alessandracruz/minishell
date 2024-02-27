/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:53:39 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/27 16:50:19 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cutstr(char *str, int start, int len)
{
	char	*pointer;
	int		counter;
	int		size;
	int		index;

	size = 0;
	counter = start;
	if (!str || start >= (int)ft_strlen(str))
		return (str);
	while (str[counter] && counter < start + (len - 1))
		counter++;
	while (str[counter + size])
		size++;
	size += start - 1;
	pointer = malloc((size + 1) * sizeof(char));
	if (!pointer)
		return (NULL);
	size = 0;
	index = 0;
	while (str[index] && size < start)
		pointer[size++] = str[index++];
	while (str[++counter])
		pointer[size++] = str[counter];
	pointer[size] = '\0';
	return(pointer);
}

char	*join_string_and_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	/*if (s2)
		free(s2);*/
	return (new_str);
}

char	*add_char_to_result(char *result, char c)
{
	char	current_char[2];

	current_char[0] = c;
	current_char[1] = '\0';
	result = join_string_and_free(result, ft_strdup(current_char));
	return (result);
}
