/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:28:58 by matlopes          #+#    #+#             */
/*   Updated: 2023/11/27 09:28:58 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstr(char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter])
		ft_putchar(str[counter++]);
	return (counter);
}
