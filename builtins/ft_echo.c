/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:50:49 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/19 10:55:04 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printv(char *str, t_minishell *shell)
{
	int		index;
	char	*var_value;
	
	index = -1;
	while (str[++index])
	{
		if (str[index] == '$')
		{
			var_value = expand_variable_in_quotes(str, shell, &index);
			index++;
			if (var_value)
			{
				index += ft_strlen(var_value);
				ft_putstr(var_value);
				free(var_value);
			}
		}
		else
			ft_putchar(str[index]);	
	}
}

bool	ft_echo(char **args, t_minishell *shell)
{
	int		newline;
	int		i;

	newline = 1;
	i = 0;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[++i])
	{
		ft_printv(args[i], shell);
		if (args[i + 1])
			ft_putchar(' ');
	}
	if (newline)
		ft_putchar('\n');
	return (true);
}
