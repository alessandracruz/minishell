/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:50:49 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/04 12:37:38 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_printnv_quotes(char *str, int index, t_minishell *shell)
{
	if (str[index] == 34)
		return (ft_printnv(str + index + 1, shell,
				ft_check_quote(str + index) - 1, true) + 1);
	else
		return (ft_printnv(str + index + 1, shell,
				ft_check_quote(str + index) - 1, false) + 1);
}

void	ft_printnv_check(char *str, int *index, t_minishell *shell)
{
	char	*var_value;

	if (str[*index + 1] == '?')
	{
		ft_putnbr(shell->exit);
		(*index)++;
	}
	else
	{
		var_value = expand_variable_in_quotes(str, shell, index);
		(*index)--;
		if (var_value)
		{
			ft_putstr(var_value);
			free(var_value);
		}
	}
}

int	ft_printnv(char *str, t_minishell *shell, int size, bool check_env)
{
	int		index;

	index = 0;
	while (str[index] && index < size)
	{
		if (check_env && ft_is_quote(str[index]) && ft_check_quote(str + index))
			index += ft_printnv_quotes(str, index, shell);
		else if (check_env && str[index] == '$')
			ft_printnv_check(str, &index, shell);
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
