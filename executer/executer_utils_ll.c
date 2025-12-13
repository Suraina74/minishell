/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_ll.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:54:54 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/12 17:39:04 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	close_fds(t_parser *tmp, t_utils_pipe *pipe_hand, int *prev_in)
{
	if (*prev_in != -1)
		close(*prev_in);
	if (tmp->next)
	{
		close(pipe_hand->fd[1]);
		*prev_in = pipe_hand->fd[0];
	}
}

void	sig_stat(int *exit_stat)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		*exit_stat = 130;
	}
	if (g_signal == SIGQUIT)
	{
		g_signal = 0;
		ft_putendl_fd("Quit (core dumped)", 2);
		*exit_stat = 131;
	}
}

void	check_fd_single_buildin(t_utils_pipe *pipe_hand)
{
	if (pipe_hand->fd_in != -1)
	{
		if (dup2(pipe_hand->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in");
			close(pipe_hand->fd_in);
		}
		close(pipe_hand->fd_in);
	}
	if (pipe_hand->fd_out != -1)
	{
		if (dup2(pipe_hand->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_out");
			close(pipe_hand->fd_out);
		}
		close(pipe_hand->fd_out);
	}
}
