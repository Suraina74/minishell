/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:58:12 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/03 15:26:35 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	heredoc_expander(char *delim)
{
	if (delim[0] == '\'' || delim[0] == '"')
	{
		printf("dont expand\n");
	}
	else
		printf("expand\n");
}

void	heredoc_start(t_parser *parser, t_utils_pipe *pipe_hand)
{
	int		hd_fd[2];
	char	*delim;

	delim = parser->redirections->next->word;
	init_pipe(hd_fd);
	while (1)
	{
		heredoc_expander(delim);
		ft_putstr_fd("heredoc > ", 1);
		parser->heredoc = get_next_line(STDIN_FILENO);
		if (!parser->heredoc)
			break ;
		if (ft_strncmp(parser->heredoc, delim, ft_strlen(delim)) == 0
			&& parser->heredoc[ft_strlen(delim)] == '\n')
		{
			free(parser->heredoc);
			break ;
		}
		write(hd_fd[1], parser->heredoc, ft_strlen(parser->heredoc));
		free(parser->heredoc);
	}
	close(hd_fd[1]);
	pipe_hand->fd_in = hd_fd[0];
}
