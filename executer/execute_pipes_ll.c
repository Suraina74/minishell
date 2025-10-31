/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_ll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:42:38 by ksoedama          #+#    #+#             */
/*   Updated: 2025/10/30 15:06:29 by ksoedama         ###   ########.fr       */
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
	tmp->child_proc = NULL;
	*cmd_struct = tmp;
}

void	fd_outs(t_utils_pipe *pipe_hand, t_parser *tmp)
{
	if (tmp->redirections->token == OUT)
	{
		tmp->redirections = tmp->redirections->next;
		pipe_hand->fd_out = open(tmp->redirections->word,
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
		dup2(pipe_hand->fd_out, STDOUT_FILENO);
		close(pipe_hand->fd_out);
	}
	if (tmp->redirections->token == OUTOUT)
	{
		tmp->redirections = tmp->redirections->next;
		pipe_hand->fd_out = open(tmp->redirections->word,
				O_CREAT | O_APPEND | O_WRONLY, 0644);
		dup2(pipe_hand->fd_out, STDOUT_FILENO);
		close(pipe_hand->fd_out);
	}
}

void	start_is_fd(t_utils_pipe *pipe_hand, t_parser *tmp)
{
	if (tmp->redirections)
	{
		fd_outs(pipe_hand, tmp);
		if (tmp->redirections->token == IN)
		{
			tmp->redirections = tmp->redirections->next;
			pipe_hand->fd_in = open(tmp->redirections->word, O_RDONLY);
			if (dup2(pipe_hand->fd_in, STDIN_FILENO) == 1)
			{
				perror("dup2");
				close(pipe_hand->fd_in);
			}
			close(pipe_hand->fd_in);
		}
	}
}

t_child_p	*give_child_back(t_utils_pipe *pid_handle)
{
	t_child_p	*new;
	t_child_p	*cur;

	new = malloc(sizeof(t_child_p));
	if (!new)
		return (NULL);
	new->id = 0;
	new->next = NULL;
	if (pid_handle->child_proc == NULL)
		pid_handle->child_proc = new;
	else
	{
		cur = pid_handle->child_proc;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (new);
}
