/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_l.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:18:07 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/01 16:58:55 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	close_fds(t_parser *tmp, t_utils_pipe *pipe_hand, int *prev_in,
		int fd[2])
{
	if (pipe_hand->child_proc > 0)
	{
		if (tmp->next != NULL)
		{
			if (*prev_in != -1)
				close(*prev_in);
			*prev_in = fd[FD_READ];
			close(fd[FD_WRITE]);
		}
		else
		{
			if (*prev_in != -1)
				close(*prev_in);
		}
	}
}

void	get_prev_pipe(t_utils_pipe *pipe_hand, t_parser *tmp, int *prev_in)
{
	if (*prev_in != -1)
	{
		if (dup2(*prev_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(*prev_in);
		}
		close(*prev_in);
	}
	if (tmp->next != NULL)
	{
		close(pipe_hand->fd[FD_READ]);
		if (dup2(pipe_hand->fd[FD_WRITE], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(pipe_hand->fd[FD_WRITE]);
		}
		close(pipe_hand->fd[FD_WRITE]);
	}
}

void	init_pipe(t_utils_pipe *pipe_hand)
{
	if (pipe(pipe_hand->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	init_child_proc(t_parser *tmp, int *prev_in, t_utils_pipe *pipe_hand,
		char **envp)
{
	pipe_hand->child_proc = fork();
	if (pipe_hand->child_proc == 0)
	{
		get_prev_pipe(pipe_hand, tmp, prev_in);
		if (build_in_flag(tmp))
		{
			execute_buildin(tmp, envp);
			exit(0);
		}
		else
			execute_fun(tmp, envp);
	}
	else if (pipe_hand->child_proc == -1)
		printf("fd error\n");
	close_fds(tmp, pipe_hand, prev_in, pipe_hand->fd);
}

char	**execute_pipes(t_parser *parser_list, char **envp)
{
	t_parser		*tmp;
	t_utils_pipe	*pipe_hand;
	int				prev_in;

	prev_in = -1;
	tmp = parser_list;
	init_cmd(&pipe_hand);
	if (build_in_flag(tmp) && tmp->next == NULL)
		envp = execute_buildin(tmp, envp);
	else
	{
		while (tmp)
		{
			init_pipe(pipe_hand);
			start_is_fd(pipe_hand, tmp);
			init_child_proc(tmp, &prev_in, pipe_hand, envp);
			tmp = tmp->next;
		}
		while (waitpid(pipe_hand->child_proc, &pipe_hand->exit_stat, 0) > 0);
		WEXITSTATUS(pipe_hand->exit_stat);
		free(pipe_hand);
	}
	return (envp);
}
