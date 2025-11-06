/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_l.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:18:07 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/06 15:32:05 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// void	close_fds(t_parser *tmp, t_utils_pipe *pipe_hand, int *prev_in,
// 		int fd[2])
// {
// 	if (pipe_hand->child_proc > 0)
// 	{
// 		if (tmp->next != NULL)
// 		{
// 			if (*prev_in != -1)
// 				close(*prev_in);
// 			*prev_in = fd[FD_READ];
// 			close(fd[FD_WRITE]);
// 		}
// 		else
// 		{
// 			if (*prev_in != -1)
// 				close(*prev_in);
// 		}
// 	}
// }

void	close_fds(t_parser *tmp, t_utils_pipe *pipe_hand, int *prev_in,
		int fd[2])
{
	if (pipe_hand->child_proc > 0)
	{
		if (*prev_in != -1)
			close(*prev_in);
		if (tmp->next != NULL)
		{
			*prev_in = fd[FD_READ];
			close(fd[FD_WRITE]);
		}
		else
		{
			close(fd[FD_READ]);
			close(fd[FD_WRITE]);
			*prev_in = -1;
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
		if (*prev_in != -1)
			dup2(*prev_in, STDIN_FILENO);

		if (tmp->next != NULL)
			dup2(pipe_hand->fd[1], STDOUT_FILENO);

		start_is_fd(pipe_hand, tmp);
		close(pipe_hand->fd[0]);
		close(pipe_hand->fd[1]);
		if (*prev_in != -1)
			close(*prev_in);

		if (build_in_flag(tmp))
			execute_buildin(tmp, envp);
		else
			execute_fun(tmp, envp);

		exit(0);
	}
	else if (pipe_hand->child_proc == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	close(pipe_hand->fd[1]);
	if (*prev_in != -1)
		close(*prev_in);
	*prev_in = pipe_hand->fd[0];
}


char	**execute_pipes(t_parser *parser_list, char **envp)
{
	t_parser		*tmp;
	t_utils_pipe	*current;
	t_utils_pipe	*pipe_hand;
	int				prev_in;
	int				saved_in;
	int				saved_out;

	prev_in = -1;
	tmp = parser_list;
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	init_cmd(&pipe_hand);
	if (tmp == NULL)
		return (NULL);
	if (build_in_flag(tmp) && tmp->next == NULL)
	{
		start_is_fd(pipe_hand, tmp);
		execute_buildin(tmp, envp);
	}
	else
	{
		while (tmp)
		{
			init_pipe(pipe_hand);
			init_child_proc(tmp, &prev_in, pipe_hand, envp);
			tmp = tmp->next;
		}
		current = pipe_hand;
		while (current)
		{
			waitpid(current->child_proc, &pipe_hand->exit_stat, 0);
			current = current->next;
		}
		WEXITSTATUS(pipe_hand->exit_stat);
	}
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	free(pipe_hand);
	return (envp);
}
