/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:34:58 by schabboe          #+#    #+#             */
/*   Updated: 2024/11/01 16:50:57 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(long n);

static int	count(long n)
{
	int	counter;

	counter = 0;
	if (n < 0)
	{
		n = n / -1;
		counter++;
	}
	if (n == 0)
		counter++;
	while (n > 0)
	{
		counter++;
		n = n / 10;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		i;
	long	number;

	number = n;
	string = (char *) malloc((count(n) + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	i = count(n) - 1;
	while (i >= 0)
	{
		if (number < 0)
			number = -number;
		string[i] = number % 10 + '0';
		number = number / 10;
		if (i == 0 && n < 0)
			string[i] = '-';
		i--;
	}
	string[count(n)] = '\0';
	return (string);
}
