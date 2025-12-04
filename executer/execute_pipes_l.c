/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_l.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:18:07 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/04 13:57:25 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	child_setup_fds(t_utils_pipe *pipe_hand, int prev_in, int is_last)
{
	fd_input(pipe_hand, &prev_in);
	fd_output(pipe_hand, &is_last);
	if (pipe_hand->fd_in != -1)
		close(pipe_hand->fd_in);
	if (prev_in != -1 && pipe_hand->fd_in == -1)
		close(prev_in);
	if (pipe_hand->fd_out != -1)
		close(pipe_hand->fd_out);
	close(pipe_hand->fd[0]);
	if (!is_last)
		close(pipe_hand->fd[1]);
}

void	init_child_proc(t_parser *tmp, t_utils_pipe *pipe_hand, char ***envp,
		int *exit_stat)
{
	int	is_last;
	int	prev_in;

	prev_in = -1;
	is_last = 0;
	pipe_hand->child_proc = fork();
	if (pipe_hand->child_proc == 0)
	{
		if (tmp->next == NULL)
			is_last = 1;
		child_setup_fds(pipe_hand, prev_in, is_last);
		if (build_in_flag(tmp))
			execute_buildin(tmp, envp);
		else
			execute_fun(tmp, exit_stat, envp);
		exit(*exit_stat);
	}
	else if (pipe_hand->child_proc < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	close_fds(tmp, pipe_hand, &prev_in);
}

int	handle_single_build_in(t_utils_pipe *pipe_hand, t_parser *tmp,
		char ***envp, int *exit_stat)
{
	int	saved_in;
	int	saved_out;

	if ((pick_redirections(pipe_hand, tmp, exit_stat, envp)) == 1)
		return (1);
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (pipe_hand->fd_in != -1)
	{
		dup2(pipe_hand->fd_in, STDIN_FILENO);
		close(pipe_hand->fd_in);
	}
	if (pipe_hand->fd_out != -1)
	{
		dup2(pipe_hand->fd_out, STDOUT_FILENO);
		close(pipe_hand->fd_out);
	}
	execute_buildin(tmp, envp);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	free(pipe_hand);
	return (0);
}

int	handle_other(t_parser *tmp, t_utils_pipe *pipe_hand, int *exit_stat,
		char ***envp)
{
	t_utils_pipe	*current;
	pid_t			last_pid;

	while (tmp)
	{
		pipe_hand->fd_in = -1;
		pipe_hand->fd_out = -1;
		if ((pick_redirections(pipe_hand, tmp, exit_stat, envp)) == 1)
			return (1);
		if (tmp->next)
			init_pipe(pipe_hand->fd);
		init_child_proc(tmp, pipe_hand, envp, exit_stat);
		if (tmp->next == NULL)
			last_pid = pipe_hand->child_proc;
		if (pipe_hand->fd_in != -1)
			close(pipe_hand->fd_in);
		if (pipe_hand->fd_out != -1)
			close(pipe_hand->fd_out);
		tmp = tmp->next;
	}
	current = pipe_hand;
	last_cmd_stat(last_pid, exit_stat);
	return (0);
}

int	execute_pipes(t_parser **parser_list, char ***envp)
{
	t_parser		*tmp;
	t_utils_pipe	*pipe_hand;
	int				exit_stat;

	exit_stat = 0;
	tmp = *parser_list;
	init_cmd(&pipe_hand);
	if (!tmp)
		return (free(pipe_hand), EXIT_FAILURE);
	if (build_in_flag(tmp) && tmp->next == NULL)
	{
		if ((handle_single_build_in(pipe_hand, tmp, envp, &exit_stat)) == 1)
			return (free_list_p(parser_list), 1);
		return (exit_stat);
	}
	else
	{
		if ((handle_other(tmp, pipe_hand, &exit_stat, envp)) == 1)
			return (free_list_p(parser_list), 1);
	}
	return (free(pipe_hand), exit_stat);
}
