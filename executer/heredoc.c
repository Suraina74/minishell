/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:58:12 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/03 14:00:08 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	heredoc_start(t_parser *parser, t_utils_pipe *pipe_hand)
{
	int		hd_fd[2];
	char	*line;
	char	*delim;

	delim = parser->redirections->next->word;
	init_pipe(hd_fd);
	while (1)
	{
		ft_putstr_fd("heredoc > ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0
			&& line[ft_strlen(delim)] == '\n')
		{
			free(line);
			break ;
		}
		write(hd_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(hd_fd[1]);
	pipe_hand->fd_in = hd_fd[0];
}
