/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:24:19 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/10 17:20:21 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	build_in_env(char ***envp)
{
	int		i;
	char	*current;

	i = 0;
	while ((*envp)[i])
	{
		current = ft_strchr((*envp)[i], '=');
		if (current && *current + 1 != '\0')
			printf("%s\n", (*envp)[i]);
		i++;
	}
	return (0);
}
