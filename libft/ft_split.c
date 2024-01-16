/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:11:15 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/16 11:55:44 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	index;
	int	start_word;
	int	count;

	count = 0;
	index = 0;
	while (s[index] != '\0')
	{
		while (s[index] == c && s[index] != '\0')
			index++;
		start_word = index;
		while (s[index] != c && s[index] != '\0')
			index++;
		if (start_word != index)
			count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	int		start_word;
	char	**pointer;
	int		word;

	index = 0;
	word = 0;
	if (!s)
		return (NULL);
	pointer = ft_calloc(ft_count(s, c) + 1, sizeof(char *));
	if (!pointer)
		return (NULL);
	while (s[index] != '\0')
	{
		while (s[index] == c && s[index] != '\0')
			index++;
		start_word = index;
		while (s[index] != c && s[index] != '\0')
			index++;
		if (start_word != index)
			pointer[word++] = ft_substr(s, start_word, index - start_word);
	}
	pointer[word] = NULL;
	return (pointer);
}

/*
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Exemplo de string e caractere delimitador
    char str[] = "Exemplo;de;uma;string;com;pontos;e;vírgulas";
    char delimiter = ';';

    // Chamada da função ft_split
    char **result = ft_split(str, delimiter);

    // Verificando se a função foi bem-sucedida
    if (result)
    {
        // Iterando sobre o resultado e imprimindo as palavras
        for (int i = 0; result[i] != NULL; ++i)
        {
            ft_printf("Palavra %d: %s\n", i + 1, result[i]);
            free(result[i]); // Liberando a memória alocada para cada palavra
        }
        free(result); // Liberando a memória alocada para o array de ponteiros
    }
    else
        ft_printf("A função ft_split falhou.\n");
    return (0);
}
*/
