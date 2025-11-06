/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:58:12 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/06 13:44:22 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	heredoc_start(t_parser *parsing, t_utils_pipe *pipe_hand)
{
	t_parser *tmp;

	pipe(pipe_hand->fd);
	pid_t new_hd;
	tmp = parsing;
	tmp->heredoc = get_next_line(pipe_hand->fd_in);
	new_hd = fork();
	if (new_hd == 0)
	{
		while (tmp->heredoc)
		{
			if (ft_strncmp(tmp->redirections->next->word, tmp->heredoc,
					ft_strlen(tmp->redirections->next->word)) == 0)
			{
				printf("found end\n");
				exit(1);
			}
			tmp->heredoc = get_next_line(pipe_hand->fd_in);
		}
	}
	else if (pipe_hand < 0)
		waitpid(new_hd, NULL, 0);
}