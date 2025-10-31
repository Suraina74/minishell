/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal_x.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:34:12 by schabboe          #+#    #+#             */
/*   Updated: 2025/07/27 16:49:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_conversion(int remainder)
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

static int	count(unsigned int number)
{
	int	count;

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

int	ft_hexadecimal_x(unsigned int number)
{
	unsigned int	remainder;
	unsigned int	quotient;

	quotient = number / 16;
	remainder = number % 16;
	if (quotient > 0)
		ft_hexadecimal_x(quotient);
	if (remainder <= 9)
		ft_putchar(remainder + '0');
	if (remainder >= 10 && remainder <= 15)
		ft_putchar(ft_conversion(remainder));
	return (count(number));
}
