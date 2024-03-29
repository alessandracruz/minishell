/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:36:07 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/10 14:25:45 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_quote(char c)
{
	if (c == 39 || c == 34)
		return (1);
	return (0);
}

int	ft_check_quote(char const *s)
{
	int		counter;
	char	quote;

	counter = 0;
	quote = s[0];
	while (s[++counter])
	{
		if (s[counter] == quote)
			return (counter);
	}
	return (0);
}

int	ft_check_inside_dquotes(char const *s, int index)
{
	char	quote;
	int		counter;
	int		check;

	counter = -1;
	check = -1;
	while (++counter < index)
	{
		if (check == -1 && s[counter] == 34)
		{
			quote = s[counter];
			check = counter;
		}
		else if (check >= 0 && s[counter] == quote)
			check = -1;
	}
	if (check == -1)
		return (-1);
	if (ft_check_quote(s + check))
		return (check);
	return (-1);
}

int	ft_check_inside_squotes(char const *s, int index)
{
	char	quote;
	int		counter;
	int		check;

	counter = -1;
	check = -1;
	while (++counter < index)
	{
		if (check == -1 && s[counter] == 39)
		{
			quote = s[counter];
			check = counter;
		}
		else if (check >= 0 && s[counter] == quote)
			check = -1;
	}
	if (check == -1)
		return (-1);
	if (ft_check_quote(s + check))
		return (check);
	return (-1);
}

int	ft_check_inside_quotes(char const *s, int index)
{
	char	quote;
	int		counter;
	int		check;

	counter = -1;
	check = -1;
	while (++counter < index)
	{
		if (check == -1 && ft_is_quote(s[counter]))
		{
			quote = s[counter];
			check = counter;
		}
		else if (check >= 0 && s[counter] == quote)
			check = -1;
	}
	if (check == -1)
		return (-1);
	if (ft_check_quote(s + check))
		return (check);
	return (-1);
}
