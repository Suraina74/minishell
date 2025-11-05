/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:58:12 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/05 15:09:38 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../mini.h>

void heredoc_start(t_utils_pipe *pipe_hand)
{
	get_next_line(pipe_hand->fd_in);
	printf("Heredoc from the other file\n");
	exit(1);
}