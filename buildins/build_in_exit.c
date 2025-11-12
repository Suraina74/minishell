/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:47 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/12 11:48:28 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	build_in_exit(t_parser *parser_list)
{
	// int i = 4;
	// if ()
	// {
		
	// }
	free_list_p(&parser_list);
	printf("exit\n");
	exit(1);
	return (0);
}
