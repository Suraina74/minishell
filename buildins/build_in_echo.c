/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:14:09 by ksoedama          #+#    #+#             */
/*   Updated: 2025/09/25 13:16:51 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static void	mk_wds(char **d2_wds, int i)
{
	ft_putstr(d2_wds[i]);
	if (d2_wds[i + 1] != NULL)
		ft_putchar(' ');
}

int	build_in_echo(char **d2_wds)
{
	size_t	i;

	i = 0;
	if (i == 0)
		i++;
	if (d2_wds[i] == NULL)
		return (ft_putchar('\n'), 0);
	if ((ft_strncmp(d2_wds[i], "-n", 3)) == 0)
	{
		i++;
		while (d2_wds[i])
			mk_wds(d2_wds, i++);
		if (d2_wds[i] == NULL)
			return (0);
	}
	while (d2_wds[i])
	{
		mk_wds(d2_wds, i);
		if (d2_wds[i + 1] == NULL)
			ft_putchar('\n');
		i++;
	}
	return (0);
}
