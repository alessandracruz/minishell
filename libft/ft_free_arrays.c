/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:41:24 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/03 20:53:38 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_arrays(char *arrays[])
{
	int	counter;

	counter = 0;
	while (arrays[counter])
		free(arrays[counter++]);
	free(arrays);
	return (-1);
}
