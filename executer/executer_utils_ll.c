/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_ll.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:54:54 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/03 19:01:10 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	close_fds(t_parser *tmp, t_utils_pipe *pipe_hand, int *prev_in)
{
	if (*prev_in != -1)
		close(*prev_in);
	if (tmp->next)
	{
		close(pipe_hand->fd[1]);
		*prev_in = pipe_hand->fd[0];
	}
}
