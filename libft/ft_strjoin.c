/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:37:44 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/11 20:54:29 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size;
	size_t	i1;
	size_t	i2;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	i1 = 0;
	while (s1[i1])
	{
		str[i1] = s1[i1];
		i1++;
	}
	i2 = 0;
	while (s2[i2])
	{
		str[i1 + i2] = s2[i2];
		i2++;
	}
	str[i1 + i2] = '\0';
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
            printf("As strings são iguais!\n");
        }
        else
        {
            printf("As strings são diferentes!\n");
        }
    }
    else
    {
        printf("Falha na alocação de memória.\n");
    }

    // Liberando memória
    free(std_strjoin_result);
    free(ft_strjoin_result);

    return 0;
}
*/
