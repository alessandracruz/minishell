/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:35:35 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/12 19:48:58 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char		*ft_extract_word(const char *s, char c, size_t *i)
{
	size_t	start;
	size_t	end;
	char	*word;

	while (s[*i] && s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	end = *i;
	word = ft_substr(s, start, end - start);
	return (word);
}

void	ft_free_split(char **array)
{
	size_t i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}


char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	size_t	i;
	size_t	j;
	char	**result;

	if (!s)
		return (NULL);
	word_count = ft_word_count(s, c);
	result = ft_calloc(word_count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		result[j] = ft_extract_word(s, c, &i);
		if (!result[j])
		{
			ft_free_split(result);
			return (NULL);
		}
		j++;
	}
	return (result);
}

#include "libft.h"
#include <stdio.h>

int main(void)
{
    char str[] = "Exemplo;de;delimitador;ponto-e-vírgula";
    char **result = ft_split(str, ';');

    if (result)
    {
        size_t i = 0;
        while (result[i])
        {
            printf("Palavra %zu: %s\n", i + 1, result[i]);
            i++;
        }

        // Liberar memória alocada
        ft_free_split(result);
    }
    else
    {
        printf("Erro ao dividir a string.\n");
    }

    return 0;
}


/*
#include "libft.h"
#include <stdio.h>

int main(void)
{
    char str1[] = "Palavra1,Palavra2,Palavra3";
    char str2[] = "OutraPalavra1 OutraPalavra2 OutraPalavra3";
    char str3[] = "Exemplo;de;delimitador;ponto-e-vírgula";

    char **result1 = ft_split(str1, ',');
    char **result2 = ft_split(str2, ' ');
    char **result3 = ft_split(str3, ';');

    // Imprime os resultados
    // ... (pode incluir uma função de impressão personalizada ou usar printf)

    // Libera a memória alocada
    ft_free_split(result1);
    ft_free_split(result2);
    ft_free_split(result3);

    return (0);
}
*/
