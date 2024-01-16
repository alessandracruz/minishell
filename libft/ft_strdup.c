/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:02:35 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/16 11:55:44 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i])
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
char	*ft_strdup2(const char *s, int begin, int end)
{
	char	*dest;
	int		len;
	int		i;

	len = end - begin + 1;
	dest = malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (begin <= end)
	{
		dest[i] = s[begin];
		i++;
		begin++;
	}
	dest[i] = '\0';
	return (dest);
}

#include <stdio.h>

int main()
{
    const char *original = "Teste de strdup";

    // Usando strdup da biblioteca padrão
    char *std_strdup_result = strdup(original);

    // Usando sua implementação ft_strdup
    char *ft_strdup_result = ft_strdup(original);

    // Comparando os resultados
    if (std_strdup_result && ft_strdup_result)
    {
        if (strcmp(std_strdup_result, ft_strdup_result) == 0)
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
    free(std_strdup_result);
    free(ft_strdup_result);

    return 0;
}
*/
