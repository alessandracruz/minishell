/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:53:10 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/16 11:55:44 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				signal;
	long long int	number;

	i = 0;
	number = 0;
	signal = 1;
	while (str[i] == ' ' || (str[i] >= 0 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10;
		number = number + str[i] - 48;
		i++;
	}
	return (number * signal);
}

/*#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *str;

    str = "    -2147483648";
    ft_printf("atoi: %d\n", atoi(str));
    ft_printf("ft_atoi: %d\n", ft_atoi(str));
}*/
