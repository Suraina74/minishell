/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:47 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/12 12:38:08 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	build_in_exit(int exit_stat, t_parser *parser_list)
{
	t_parser	*tmp;

	tmp = parser_list;
	if (tmp && tmp->words[0])
	{
		if (tmp->words[1])
		{
			if (!is_numeric(tmp->words[1]))
			{
				exit_stat = 2;
				ft_putendl_fd("numeric argument required", 2);
				exit(exit_stat);
			}
			exit_stat = ft_atoi(tmp->words[1]);
		}
		else
			exit_stat = 0;
	}
	free_list_p(&parser_list);
	printf("exit\n");
	exit(exit_stat);
}
