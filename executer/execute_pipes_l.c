/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_l.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:18:07 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/08 14:56:08 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	init_pipe(t_utils_pipe *pipe_hand)
{
	if (pipe(pipe_hand->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	get_prev_pipe(t_utils_pipe *pipe_hand, t_parser *tmp, int *prev_in)
{
	if (*prev_in != -1)
	{
		if (dup2(*prev_in, STDIN_FILENO) == -1)
		{
			close(*prev_in);
			exit(1);
		}
	}
	if (tmp->next != NULL)
	{
		if (dup2(pipe_hand->fd[1], STDOUT_FILENO) == -1)
		{
			close(pipe_hand->fd[1]);
			exit(1);
		}
	}
	start_is_fd(pipe_hand, tmp);
	close(pipe_hand->fd[0]);
	close(pipe_hand->fd[1]);
	if (*prev_in != -1)
		close(*prev_in);
}

void	init_child_proc(t_parser *tmp, int *prev_in, t_utils_pipe *pipe_hand,
		char ***envp)
{
	pipe_hand->child_proc = fork();
	if (pipe_hand->child_proc == 0)
	{
		get_prev_pipe(pipe_hand, tmp, prev_in);
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

int	execute_pipes(t_parser *parser_list, char ***envp)
{
	t_parser		*tmp;
	t_utils_pipe	*current;
	t_utils_pipe	*pipe_hand;
	int				prev_in;
	int				saved_in;
	int				saved_out;
	int				exit_stat;

	exit_stat = -1;
	prev_in = -1;
	tmp = parser_list;
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	init_cmd(&pipe_hand);
	if (tmp == NULL)
	{
		free(pipe_hand);
		return (exit_stat);
	}
	if (build_in_flag(tmp) && tmp->next == NULL)
	{
		start_is_fd(pipe_hand, tmp);
		execute_buildin(tmp, envp);
		free(pipe_hand);
		return (exit_stat);
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
		waitpid(current->child_proc, &exit_stat, 0);
		while (waitpid(-1, &exit_stat, 0) > 0)
			;
		WEXITSTATUS(exit_stat);
	}
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	free(pipe_hand);
	return (exit_stat);
}
