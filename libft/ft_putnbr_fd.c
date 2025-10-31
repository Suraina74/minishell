/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:38:19 by schabboe          #+#    #+#             */
/*   Updated: 2024/11/01 16:51:52 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	number;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		n = n * -1;
		write(fd, "-", 1);
	}
	if (n >= 0 && n <= 9)
	{
		number = n + '0';
		write(fd, &number, 1);
	}
	if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		number = n % 10 + '0';
		write(fd, &number, 1);
	}
}
