/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_us.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:14:43 by schabboe          #+#    #+#             */
/*   Updated: 2025/07/27 16:51:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(unsigned int number)
{
	int	count;

	count = 0;
	if (number == 0)
		count = 1;
	while (number > 0)
	{
		number = number / 10;
		count++;
	}
	return (count);
}

int	ft_putnbr_us(unsigned int n)
{
	unsigned int	number;

	number = n;
	if (n > 0 && n <= 9)
	{
		ft_putchar(n + '0');
	}
	if (n > 9)
	{
		ft_putnbr_us((n / 10));
		ft_putchar(n % 10 + '0');
	}
	return (count(number));
}
