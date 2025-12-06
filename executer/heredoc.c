/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:58:12 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/06 20:10:17 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	delete_quotes(char **delim)
{
	int		i;
	int		j;
	char	new_delim[100000];

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
				*word = ft_strjoin(new_word, "\n");
				if (*word == NULL)
					return (1);
				free(new_word);
			}
			i++;
		}
	}
	return (0);
}

int	heredoc_start(t_parser *parser, t_utils_pipe *pipe_hand, int *exit_stat,
		char ***envp)
{
	int		hd_fd[2];
	char	*delim;

	init_signals_heredoc();
	delim = parser->redirections->next->word;
	init_pipe(hd_fd);
	while (1 && g_signal != SIGINT)
	{
		parser->heredoc = readline("heredoc > ");
		if (parser->heredoc == NULL)
			break ;
		if ((heredoc_expander(&parser->heredoc, &delim, envp, exit_stat)) == 1)
			return (free(parser->heredoc), 1);
		if (!parser->heredoc)
			break ;
		if (ft_strncmp(parser->heredoc, delim, ft_strlen(delim)) == 0
			&& parser->heredoc[ft_strlen(delim)] == '\0')
		{
			free(parser->heredoc);
			break ;
		}
		write(hd_fd[1], parser->heredoc, ft_strlen(parser->heredoc));
		write(hd_fd[1], "\n", 1);
		free(parser->heredoc);
	}
	if (g_signal == SIGINT)
	{
		close(hd_fd[1]);
		pipe_hand->fd_in = hd_fd[0];
		// free(parser->heredoc);
		g_signal = 0;
		parser->heredoc = NULL;
		return (130);
	}
	close(hd_fd[1]);
	pipe_hand->fd_in = hd_fd[0];
	return (0);
}
