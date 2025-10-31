/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:13:03 by schabboe          #+#    #+#             */
/*   Updated: 2024/11/01 16:49:58 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*temp_string;
	size_t	i;

	i = 0;
	temp_string = (char *)s;
	while (i < n)
	{
		temp_string[i] = '\0';
		i++;
	}
}
