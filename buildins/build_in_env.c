/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:24:19 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/26 20:04:29 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int build_in_env(char ***envp)
{
	int i;
	int	j;

	i = 0;
	while ((*envp)[i])
	{
		j = 0;
		if ((ft_strchr((*envp)[i], '=') != NULL))
		{
			while ((*envp)[i][j])
			{
				if ((*envp)[i][j] == '=' && (*envp)[i][j + 1] != '\0')
				{
					printf("%s\n", (*envp)[i]);
					break ;
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}
