/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:50:49 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/16 15:06:46 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void	ft_echo(char **args)
{
	bool	no_newline;
	int		i;
	char	*processed_arg;

	no_newline = false;
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		no_newline = true;
		i++;
	}
	while (args[i])
	{
		processed_arg = process_argument(args[i]);
		printf("%s", processed_arg);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
}

char	*process_argument(char *arg)

