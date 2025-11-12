/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:47 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/12 12:24:22 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	build_in_exit(int exit_stat, t_parser *parser_list)
{
	t_parser	*tmp;

	tmp = parser_list;
	if (tmp && tmp->words[0])
	{
		if (tmp->words[1])
			exit_stat = ft_atoi(tmp->words[1]);
		else
			exit_stat = 0;
	}
	free_list_p(&parser_list);
	printf("exit\n");
	exit(exit_stat);
}
