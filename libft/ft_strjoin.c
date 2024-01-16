/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:37:44 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/16 16:55:22 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	index;
	size_t	counter;

	if (!s1 && !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	index = 0;
	if (s1)
	{
		while (*s1)
			str[index++] = *s1++;
	}
	counter = -1;
	if (s2)
	{
		while (s2[++counter])
			str[index + counter] = s2[counter];
	}
	str[index + counter] = '\0';
	return (str);
}

/*
#include <stdio.h>

int main()
{
    const char *str1 = "Hello, ";
    const char *str2 = "world!";

    // Usando strjoin da biblioteca padrão
    char *std_strjoin_result = strdup(str1);
    strcat(std_strjoin_result, str2);

    // Usando sua implementação ft_strjoin
    char *ft_strjoin_result = ft_strjoin(str1, str2);

    // Comparando os resultados
    if (std_strjoin_result && ft_strjoin_result)
    {
        if (strcmp(std_strjoin_result, ft_strjoin_result) == 0)
        {
            ft_printf("As strings são iguais!\n");
        }
        else
        {
            ft_printf("As strings são diferentes!\n");
        }
    }
    else
    {
        ft_printf("Falha na alocação de memória.\n");
    }

    // Liberando memória
    free(std_strjoin_result);
    free(ft_strjoin_result);

    return 0;
}
*/
