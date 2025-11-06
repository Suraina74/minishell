/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_ll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:42:38 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/06 17:18:35 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	init_cmd(t_utils_pipe **cmd_struct)
{
	t_utils_pipe	*tmp;

	tmp = malloc(sizeof(t_utils_pipe));
	if (!tmp)
		return ;
	tmp->command = NULL;
	tmp->exit_stat = -1;
	tmp->fd_in = -1;
	tmp->fd_out = -1;
	tmp->next = NULL;
	tmp->child_proc = -1;
	*cmd_struct = tmp;
}

void	fd_outs(t_utils_pipe *pipe_hand, t_parser *parser)
{
	t_parser *tmp;

	tmp = parser;
	if (tmp->redirections->token == OUT)
	{
		pipe_hand->fd_out = open(tmp->redirections->next->word,
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (dup2(pipe_hand->fd_out, STDOUT_FILENO) == -1)
		{
			perror("Dup2");
		}
		close(pipe_hand->fd_out);
	}
	if (tmp->redirections->token == OUTOUT)
	{
		pipe_hand->fd_out = open(tmp->redirections->next->word,
				O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (dup2(pipe_hand->fd_out, STDOUT_FILENO) == -1)
		{
			perror("Dup2");
		}
		close(pipe_hand->fd_out);
	}
}

void	start_is_fd(t_utils_pipe *pipe_hand, t_parser *parser)
{
	t_parser *tmp;
	
	tmp = parser;
	if (tmp->redirections)
	{
		fd_outs(pipe_hand, tmp);
		if (tmp->redirections->token == IN)
		{
			pipe_hand->fd_in = open(tmp->redirections->next->word, O_RDONLY);
			if (dup2(pipe_hand->fd_in, STDIN_FILENO) == -1)
			{
				perror("dup2");
				close(pipe_hand->fd_in);
			}
			close(pipe_hand->fd_in);
		}
		if (tmp->redirections->token == ININ)
		{
			pipe_hand->fd_in = 0;
			heredoc_start(tmp, pipe_hand);
		}
	}
	tmp = parser;
}
