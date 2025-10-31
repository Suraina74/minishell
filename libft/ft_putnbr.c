/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:14:52 by schabboe          #+#    #+#             */
/*   Updated: 2025/05/24 13:07:56 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int number)
{
	int	count;

	count = 0;
	if (number == 0)
		count = 1;
	if (number < 0)
	{
		count++;
		number = number * -1;
	}
	while (number > 0)
	{
		number = number / 10;
		count++;
	}
	return (count);
}

int	ft_putnbr(int n)
{
	int	number;

	number = n;
	if (n == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		else
			return (11);
	}
	else if (n < 0)
	{
		n = n * -1;
		ft_putchar('-');
	}
	if (n >= 0 && n <= 9)
	{
		ft_putchar(n + '0');
	}
	if (n > 9)
	{
		ft_putnbr((n / 10));
		ft_putchar(n % 10 + '0');
	}
	return (count(number));
}
