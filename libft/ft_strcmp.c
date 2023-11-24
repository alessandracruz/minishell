/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:04:26 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/23 13:43:38 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int    ft_strcmp(const char *s1, const char *s2)
{
	int i;
	
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s1 = "ABC";
	char *s2 = "ABCD";
	printf("ft_strcmp: %d\n", ft_strcmp(s1, s2));
	printf("strcmp: %d\n", strcmp(s1, s2));
}
*/

