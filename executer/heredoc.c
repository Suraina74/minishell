/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:58:12 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/13 14:12:11 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	delete_quotes(char **delim)
{
	int			i;
	int			j;
	static char	new_delim[100000];

	i = 1;
	j = 0;
	while ((*delim)[i + 1] != '\0')
	{
		new_delim[j] = (*delim)[i];
		i++;
		j++;
	}
	new_delim[j] = '\0';
	*delim = new_delim;
}

int	heredoc_expander(char **word, char **delim, char ***envp, int *exit_stat)
{
	int		i;
	char	*new_word;

	i = 0;
	if ((*delim)[0] == '\'' || (*delim)[0] == '\"')
		delete_quotes(delim);
	else
	{
		while ((*word)[i])
		{
			if ((*word)[i] == '$')
			{
				new_word = actions_if_dollar_found(*word,
						&i, *envp, *exit_stat);
				if (new_word == NULL)
					return (1);
				*word = new_word;
			}
			i++;
		}
	}
	return (0);
}

static void	setup(int *hd_fd)
{
	init_signals_heredoc();
	init_pipe(hd_fd);
}

void	set_delim_and_heredoc(char **delim, t_parser **parser)
{
	t_lexer	*tmp_red;

	(*parser)->heredoc = readline("heredoc > ");
	tmp_red = (*parser)->redirections;
	while (tmp_red)
	{
		if (tmp_red->token == ININ)
		{
			*delim = tmp_red->next->word;
			break ;
		}
		tmp_red = tmp_red->next;
	}
}

int	heredoc_start(t_parser *parser, t_utils_pipe *pipe_hand, int *exit_stat,
		char ***envp)
{
	int			hd_fd[2];
	char		*delim;

	setup(hd_fd);
	while (1 && g_signal != SIGINT)
	{
		set_delim_and_heredoc(&delim, &parser);
		if (parser->heredoc == NULL)
		{
			ft_putendl_fd("warning: here-document delimited by end-of-file", 2);
			break ;
		}
		if ((heredoc_expander(&parser->heredoc, &delim, envp, exit_stat)) == 1)
			return (close(hd_fd[0]), close(hd_fd[1]), free(parser->heredoc), \
free(pipe_hand), 1);
		if (!parser->heredoc)
			break ;
		if (ft_strncmp(parser->heredoc, delim, ft_strlen(delim)) == 0 \
&& ft_strlen(delim) == ft_strlen(parser->heredoc))
		{
			free(parser->heredoc);
			break ;
		}
		ft_putendl_fd(parser->heredoc, hd_fd[1]);
		free(parser->heredoc);
	}
	return (close(hd_fd[1]), pipe_hand->fd_in = hd_fd[0], init_signals(), 0);
}
