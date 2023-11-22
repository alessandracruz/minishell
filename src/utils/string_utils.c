/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:53:39 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/22 12:15:30 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_string_and_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
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
