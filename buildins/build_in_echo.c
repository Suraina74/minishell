/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:14:09 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/05 15:55:18 by ksoedama         ###   ########.fr       */
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
	size_t	j;
	int		nl;

	nl = 1;
	i = 1;
	if (d2_wds[i] == NULL)
		return (ft_putchar('\n'), 0);
	while (d2_wds[i][0] == '-' && d2_wds[i][1] == 'n')
	{
		j = 2;
		while (d2_wds[i][j] == 'n')
			j++;
		if (d2_wds[i][j] != '\0')
			break ;
		nl = 0;
		i++;
	}
	while (d2_wds[i])
		mk_wds(d2_wds, i++);
	if (nl)
		ft_putchar('\n');
	return (0);
}
