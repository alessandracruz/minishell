/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:53:35 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/03 20:52:35 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arguments(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
		free(arguments[i++]);
	free(arguments);
}

int	arguments_counter(char **argv)
{
	int	index;

	index = 0;
	while (argv[index])
		index++;
	return (index);
}
