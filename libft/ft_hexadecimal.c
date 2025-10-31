/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:34:26 by schabboe          #+#    #+#             */
/*   Updated: 2025/07/27 16:32:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_conversion(int remainder)
{
	char	hex;

	hex = '\0';
	if (remainder == 10)
		hex = 'A';
	else if (remainder == 11)
		hex = 'B';
	else if (remainder == 12)
		hex = 'C';
	else if (remainder == 13)
		hex = 'D';
	else if (remainder == 14)
		hex = 'E';
	else if (remainder == 15)
		hex = 'F';
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

int	ft_hexadecimal(unsigned int number)
{
	unsigned int	remainder;
	unsigned int	quotient;

	quotient = number / 16;
	remainder = number % 16;
	if (quotient > 0)
		ft_hexadecimal(quotient);
	if (remainder <= 9)
		ft_putchar(remainder + '0');
	if (remainder >= 10 && remainder <= 15)
		ft_putchar(ft_conversion(remainder));
	return (count(number));
}
