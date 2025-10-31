/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_l.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:18:07 by ksoedama          #+#    #+#             */
/*   Updated: 2025/10/30 18:48:56 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void close_fds(t_parser *tmp, t_child_p *new_child, int *prev_in, int fd[2])
{
	if (new_child->id > 0)
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
	start_is_fd(pipe_hand, tmp);
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

void init_pipe(t_parser *tmp, t_utils_pipe *pipe_hand)
{
	if (tmp->next != NULL)
	{
		if (pipe(pipe_hand->fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

void	init_child_proc(t_parser *tmp, int *prev_in, t_utils_pipe *pipe_hand, char **envp)
{
	t_child_p	*new_child;

	new_child = give_child_back(pipe_hand);
	new_child->id = fork();
	if (new_child->id == 0)
	{
		get_prev_pipe(pipe_hand, tmp, prev_in);
		execute_fun(tmp, envp);
	}
	else if (new_child->id == -1)
		printf("fd error\n");
	close_fds(tmp, new_child, prev_in, pipe_hand->fd);
}

char **execute_pipes(t_parser *parser_list, char **envp)
{
	t_parser		*tmp;
	t_child_p		*current;
	t_utils_pipe	*pipe_hand;
	int				prev_in;

	prev_in = -1;
	tmp = parser_list;
	init_cmd(&pipe_hand);
	if (build_in_flag(tmp) && tmp->next != NULL)
		envp = check_if_buildin(tmp, envp);
	else
	{
		while (tmp)
		{
			init_pipe(tmp, pipe_hand);
			if (build_in_flag(tmp))
				envp = check_if_buildin(tmp, envp);
			else if (!build_in_flag(tmp))
				init_child_proc(tmp, &prev_in, pipe_hand, envp);
			tmp = tmp->next;
		}
		current = pipe_hand->child_proc;
		while (current)
		{
			WEXITSTATUS(pipe_hand->exit_stat);
			waitpid(current->id, &pipe_hand->exit_stat, 0);
			current = current->next;
		}
		// free(pipe_hand->child_proc);
		free(pipe_hand);
	}
	return (envp);
}
