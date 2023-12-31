/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:50:49 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/16 23:52:43 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args, t_minishell *shell)
{
	int		newline;
	int		i;
	char	*processed_arg;

	newline = 1;
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		processed_arg = handle_quotes(args[i], shell);
		if (processed_arg)
		{
			printf("%s", processed_arg);
			free(processed_arg);
		}
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
