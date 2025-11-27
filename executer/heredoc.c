/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:58:12 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/27 19:22:22 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// void	heredoc_start(t_parser *parsing)
// {
// 	t_parser	*tmp;
// 	char		*line_history;
// 	char		*line;
// 	char		*delim;
// 	int			heredoc_fd[2];

// 	line_history = NULL;
// 	tmp = parsing;
// 	delim = tmp->redirections->next->word;
// 	init_pipe(heredoc_fd);
// 	ft_putstr("heredoc > ");
// 	line = get_next_line(STDIN_FILENO);
// 	if (!line)
// 		return ;
// 	while (ft_strncmp(delim, line, ft_strlen(delim)))
// 	{
// 		ft_putstr("heredoc > ");
// 		if (line_history)
// 			line_history = ft_strjoin(line_history, line);
// 		else
// 			line_history = line;
// 		write(heredoc_fd[1], line_history, ft_strlen(line_history));
// 		line = get_next_line(STDIN_FILENO);
// 		if (!line)
// 			break ;
// 	}
// 	tmp->heredoc = line_history;
// 	close(heredoc_fd[0]);
// 	close(heredoc_fd[1]);
// }

void	heredoc_start(t_parser *parser, t_utils_pipe *pipe_hand)
{
	int		hd[2];
	char	*line;
	char	*delim;

	delim = parser->redirections->next->word;
	pipe(hd);
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
		write(hd[1], line, ft_strlen(line));
		free(line);
	}
	close(hd[1]);
	pipe_hand->fd_in = hd[0];
}
