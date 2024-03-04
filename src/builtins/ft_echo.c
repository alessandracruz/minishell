/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:50:49 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/03 20:37:51 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_printnv(char *str, t_minishell *shell, int size, bool check_env)
{
	int		index;
	char	*var_value;

	index = 0;
	while (str[index] && index < size)
	{
		if (check_env && (str[index] == 34 || str[index] == 39)
			&& ft_check_quote(str + index))
		{
			if (str[index] == 34)
				index += ft_printnv(str + index + 1, shell,
						ft_check_quote(str + index) - 1, true) + 1;
			else
				index += ft_printnv(str + index + 1, shell,
						ft_check_quote(str + index) - 1, false) + 1;
		}
		else if (check_env && str[index] == '$')
		{
			if (str[index + 1] == '?')
			{
				ft_putnbr(shell->exit);
				index++;
			}
			else
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
		}
		else
			ft_putchar(str[index]);
		index++;
	}
	return (index);
}

bool	ft_echo(char **args, t_minishell *shell)
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
		ft_printnv(args[i], shell, ft_strlen(args[i]), true);
		if (args[i + 1])
			ft_putchar(' ');
	}
	if (newline)
		ft_putchar('\n');
	return (true);
}
