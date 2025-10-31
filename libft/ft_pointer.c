/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:52:41 by schabboe          #+#    #+#             */
/*   Updated: 2025/07/27 16:50:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_conversion(uintptr_t remainder)
{
	char	hex;

	hex = '\0';
	if (remainder == 10)
		hex = 'a';
	else if (remainder == 11)
		hex = 'b';
	else if (remainder == 12)
		hex = 'c';
	else if (remainder == 13)
		hex = 'd';
	else if (remainder == 14)
		hex = 'e';
	else if (remainder == 15)
		hex = 'f';
	return (hex);
}

static int	count(uintptr_t number)
{
	size_t	count;

	count = 0;
	if (number == 0)
		count = 1;
	while (number > 0)
	{
		count++;
		number = number / 16;
	}
	return (count);
}

static int	ft_hexapointer(uintptr_t number)
{
	size_t	remainder;
	size_t	quotient;

	quotient = number / 16;
	remainder = number % 16;
	if (quotient > 0)
		ft_hexapointer(quotient);
	if (remainder <= 9)
		ft_putchar(remainder + '0');
	if (remainder >= 10 && remainder <= 15)
		ft_putchar(ft_conversion(remainder));
	return (count(number));
}

int	ft_pointer(uintptr_t n)
{
	size_t	count;

	if (n == 0)
	{
		if (write(1, "(nil)", 5) == -1)
			return (-1);
		else
			return (5);
	}
	ft_putchar('0');
	ft_putchar('x');
	count = 2;
	count = count + ft_hexapointer(n);
	return (count);
}
