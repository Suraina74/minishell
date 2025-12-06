/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:32:37 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/06 15:37:28 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	build_in_cd(char **d2_array)
{
	if (d2_array[1] == NULL)
		return (ft_putendl_fd("cd: only with relative or absolute path", 2)
			, 1);
	if (d2_array[1] && d2_array[2])
		return (ft_putendl_fd("cd: too many arguments", 2), 1);
	if (chdir(d2_array[1]) == -1)
		return (perror("cd"), 1);
	return (0);
}
