/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:58:12 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/27 18:35:36 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	heredoc_start(t_parser *parsing, t_utils_pipe *pipe_hand)
{
	t_parser	*tmp;
	char		*line_history;
	char		*line;
	char		*delim;

	line_history = NULL;
	tmp = parsing;
	delim = tmp->redirections->next->word;
	if (pipe(pipe_hand->fd) == -1)
	{
		perror("pipe");
		return ;
	}
	ft_putstr("heredoc > ");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return ;
	while (ft_strncmp(delim, line, ft_strlen(delim)))
	{
		ft_putstr("heredoc > ");
		if (line_history)
			line_history = ft_strjoin(line_history, line);
		else
			line_history = line;
		write(pipe_hand->fd[1], line_history, ft_strlen(line_history));
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
	}
	tmp->heredoc = line_history;
	close(pipe_hand->fd[0]);
	close(pipe_hand->fd[1]);
}
