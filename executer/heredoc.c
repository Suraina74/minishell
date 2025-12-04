/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:58:12 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/04 13:32:15 by schabboe         ###   ########.fr       */
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
		while ((*word)[i])
		{
			if ((*word)[i] == '$')
			{
				new_word = actions_if_dollar_found(*word, &i, *envp, *exit_stat);
				if (new_word == NULL)
					return (1);
				*word = ft_strjoin(new_word, "\n");
				if (*word == NULL)
					return (1);
				free(new_word);
			}
			i++;
		}
	return (0);
}

int	heredoc_start(t_parser *parser, t_utils_pipe *pipe_hand, int *exit_stat,
		char ***envp)
{
	int		hd_fd[2];
	char	*delim;

	delim = parser->redirections->next->word;
	init_pipe(hd_fd);
	while (1)
	{
		ft_putstr_fd("heredoc > ", 1);
		parser->heredoc = get_next_line(STDIN_FILENO);
		if ((heredoc_expander(&parser->heredoc, &delim, envp, exit_stat)) == 1)
			return (free(parser->heredoc), 1);
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
	return (0);
}
