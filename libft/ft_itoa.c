/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:45:23 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/12 18:59:15 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Função auxiliar para calcular o comprimento do número
static	size_t	calculate_length(long num)
{
	size_t	length;

	length = 0;
	if (num < 0)
	{
		length++;
		num *= -1;
	}
	while (num > 9)
	{
		length++;
		num /= 10;
	}
	length++;
	return (length);
}

char	*ft_itoa(int nbr)
{
	char	*result;
	long	number;
	size_t	len;

	number = nbr;
	len = calculate_length(number);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (result);
	if (number < 0)
	{
		result[0] = '-';
		number *= -1;
	}
	result[len] = '\0';
	while (len > 0)
	{
		if (number / 10 < 1)
			break ;
		result[len-- - 1] = (number % 10) + '0';
		number /= 10;
	}
	result[len - 1] = number + '0';
	return (result);
}

/*
#include <limits.h>
#include <stdio.h>

int main(void)
{
	int number = INT_MAX;
	int number1 = INT_MIN;
	int number2 = 0;
	int number3 = 156;
	int number4 = -55;
	printf("str: %s\n", ft_itoa(number));
	printf("str: %s\n", ft_itoa(number1));
	printf("str: %s\n", ft_itoa(number2));
	printf("str: %s\n", ft_itoa(number3));
	printf("str: %s\n", ft_itoa(number4));
}
*/

/* Entendendo a ft_itoa.c por partes com comentários:

Função auxiliar para calcular o comprimento do número

static size_t calculate_length(long num)
{
    size_t length = 0;

    // Considera o sinal negativo
    if (num < 0)
    {
        length++;
        num *= -1;
    }

    // Calcula o comprimento contando os dígitos
    while (num > 9)
    {
        length++;
        num /= 10;
    }
    length++;

    return (length);
}

// Função principal para converter int para string
char *ft_itoa(int nbr)
{
    char *result;
    long number; // Usa long para evitar problemas com INT_MIN
    size_t len;

    number = nbr;
    len = calculateLength(number);

    // Aloca memória para a string resultante
    result = (char *)malloc(sizeof(char) * (len + 1));
    if (result == NULL)
        return (result);

    // Lida com o sinal negativo
    if (number < 0)
    {
        result[0] = '-';
        number *= -1;
    }

    // Preenche a string resultante
    result[len] = '\0';
    while (len > 0)
    {
        if (number / 10 < 1)
            break;
        result[len-- - 1] = (number % 10) + '0'; // Converte para caractere ASCII
        number /= 10;
    }
    result[len - 1] = number + '0';

    return (result);
}
*/
