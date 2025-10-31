/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:38:12 by schabboe          #+#    #+#             */
/*   Updated: 2024/11/01 16:53:33 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (s[i] + 1 == (char)c)
		return ((char *) &s[i]);
	else
	{
		while (i >= 0)
		{
			if (s[i] == (char)c)
				return ((char *) &s[i]);
			i--;
		}
	}
	return (NULL);
}
