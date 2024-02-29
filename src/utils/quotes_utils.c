/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:36:07 by matlopes          #+#    #+#             */
/*   Updated: 2024/02/28 12:15:37 by matlopes         ###   ########.fr       */
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