/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:32:37 by ksoedama          #+#    #+#             */
/*   Updated: 2025/10/22 13:54:23 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	build_in_cd(char **d2_array)
{
	char	s[100];
	size_t	i;

	i = 0;
	while (d2_array[i])
	{
		chdir(d2_array[i]);
		if (d2_array[i] == NULL)
			printf("error\n");
		i++;
	}
	printf("%s\n", getcwd(s, 100));
	return (0);
}
