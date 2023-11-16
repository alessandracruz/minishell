/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:42:19 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/11 19:45:53 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy2(char *dest, char *src, int size)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && size > 0)
	{
		dest[i] = src[i];
		i++;
		size--;
	}
	return (dest);
}
