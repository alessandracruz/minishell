/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:34:21 by matlopes          #+#    #+#             */
/*   Updated: 2024/01/16 11:56:13 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_str(char *str)
{
	if (!str)
		return (ft_putstr("(null)"));
	return (ft_putstr(str));
}

static int	ft_print_base(unsigned long n, char c)
{
	int	size;
	int	base;

	size = 1;
	if (c == 'p')
	{
		if (!n)
			return (ft_print_str("(nil)"));
		return (ft_print_str("0x") + ft_print_base(n, 'x'));
	}
	if (c == 'd' || c == 'i' || c == 'u')
		base = 10;
	else
		base = 16;
	if (n / base)
		size += ft_print_base(n / base, c);
	if (c == 'X')
		ft_putchar("0123456789ABCDEF"[n % base]);
	else
		ft_putchar("0123456789abcdef"[n % base]);
	return (size);
}

static int	ft_print_nbr(int nb, char c)
{
	long int	value;

	value = nb;
	if (value < 0)
		return (ft_putchar('-') + ft_print_base(-value, c));
	return (ft_print_base(value, c));
}

static int	ft_conversions(char c, va_list arg)
{
	if (c == 'c')
		return (ft_putchar(va_arg(arg, int)));
	if (c == 's')
		return (ft_print_str(va_arg(arg, char *)));
	if (c == 'p')
		return (ft_print_base(va_arg(arg, unsigned long), c));
	if (c == 'd' || c == 'i')
		return (ft_print_nbr(va_arg(arg, int), c));
	if (c == 'u' || c == 'x' || c == 'X')
		return (ft_print_base(va_arg(arg, unsigned int), c));
	if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		counter;
	va_list	arg;

	counter = 0;
	if (!str)
		return (-1);
	va_start(arg, str);
	while (*str)
	{
		if (*str == '%' && ft_strchr("cspdiuxX%", str[1]))
			counter += ft_conversions(*++str, arg);
		else
			counter += ft_putchar(*str);
		str++;
	}
	va_end(arg);
	return (counter);
}
