/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:50:49 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/10 16:38:59 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_echo(char **args)
{
	int	newline;
	int	i;

	newline = 1;
	i = 0;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[++i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			ft_putchar(' ');
	}
	if (newline)
		ft_putchar('\n');
	return (true);
}
