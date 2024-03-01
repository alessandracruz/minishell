/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:42:49 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/01 11:13:01 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return ((void *)0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start >= len)
		str = malloc((len + 1) * sizeof(char));
	else
		str = malloc(((ft_strlen(s) - start) + 1) * sizeof(char));
	if (!str)
		return ((void *)0);
	ft_strlcpy(str, (s + start), (len + 1));
	return (str);
}
