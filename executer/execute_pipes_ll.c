/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_ll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:42:38 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/09 19:00:50 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	out_redir(t_lexer *tmp_red, t_utils_pipe *pipe_hand)
{
	if (tmp_red->token == OUT)
	{
		pipe_hand->fd_out = open(tmp_red->next->word,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipe_hand->fd_out == -1)
			return (perror("open"), 1);
	}
	else if (tmp_red->token == OUTOUT)
	{
		pipe_hand->fd_out = open(tmp_red->next->word,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (pipe_hand->fd_out == -1)
			return (perror("open"), 1);
	}
	return (0);
}

int	pick_redirections(t_utils_pipe *pipe_hand, t_parser *parser,
		int *exit_stat, char ***envp)
{
	t_lexer	*tmp_red;

	tmp_red = parser->redirections;
	while (tmp_red)
	{
		if (out_redir(tmp_red, pipe_hand))
			return (1);
		if (tmp_red->token == IN)
		{
			pipe_hand->fd_in = open(tmp_red->next->word, O_RDONLY);
			if (pipe_hand->fd_in == -1)
				return (perror("open"), 1);
		}
		else if (tmp_red->token == ININ)
		{
			if ((heredoc_start(parser, pipe_hand, exit_stat, envp)) == 1)
				return (1);
		}
		tmp_red = tmp_red->next;
	}
	return (0);
}

void	fd_input(t_utils_pipe *pipe_hand, int *prev_in)
{
	if (pipe_hand->fd_in != -1)
	{
		if (dup2(pipe_hand->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(pipe_hand->fd_in);
			return ;
		}
	}
	else if (*prev_in != -1)
	{
		if (dup2(*prev_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(*prev_in);
			return ;
		}
	}
}

void	fd_output(t_utils_pipe *pipe_hand, int *is_last)
{
	if (pipe_hand->fd_out != -1)
	{
		if (dup2(pipe_hand->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(pipe_hand->fd_out);
			return ;
		}
	}
	else if (!*is_last)
	{
		if (dup2(pipe_hand->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(pipe_hand->fd[1]);
			return ;
		}
	}
}
