/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:33:22 by schabboe          #+#    #+#             */
/*   Updated: 2024/11/01 16:52:48 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;

	len_dst = 0;
	len_src = 0;
	while (dst[len_dst] != '\0')
	{
		len_dst++;
	}
	while (src[len_src] != '\0')
	{
		len_src++;
	}
	if (len_dst >= size)
		return (size + len_src);
	if (len_src > ((size - 1) - len_dst))
	{
		ft_memcpy((dst + len_dst), src, (size - len_dst - 1));
		dst[size - 1] = '\0';
	}
	else
		ft_memcpy((dst + len_dst), src, len_src + 1);
	return (len_dst + len_src);
}
