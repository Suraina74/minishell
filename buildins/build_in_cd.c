/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:32:37 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/13 12:07:35 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	build_in_cd(char **d2_array, int *exit_stat)
{
	if (d2_array[1] == NULL)
	{
		*exit_stat = 1;
		return (ft_putendl_fd("cd: only with relative or absolute path", 2),
			*exit_stat);
	}
	if (d2_array[1][0] == '-')
	{
		*exit_stat = 2;
		return (ft_putendl_fd("cd: - invalid option", 2), *exit_stat);
	}
	if (d2_array[1] && d2_array[2])
	{
		*exit_stat = 1;
		return (ft_putendl_fd("cd: too many arguments", 2), *exit_stat);
	}
	if (chdir(d2_array[1]) == -1)
	{
		*exit_stat = 1;
		return (perror("cd"), *exit_stat);
	}
	return (0);
}
