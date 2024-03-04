/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:36:07 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/03 20:52:32 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_check_inside_quotes(char const *s, int index)
{
	char	quote;
	int		counter;
	int		check;

	counter = -1;
	check = -1;
	while (++counter < index)
	{
		if (check == -1 && (s[counter] == 34 || s[counter] == 39))
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
