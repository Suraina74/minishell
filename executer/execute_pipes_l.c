/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_l.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:18:07 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/13 11:15:49 by schabboe         ###   ########.fr       */
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
	if (pipe_hand->fd[0] != STDIN_FILENO)
		close(pipe_hand->fd[0]);
	if (!is_last)
		close(pipe_hand->fd[1]);
}

void	init_child_proc(t_parser *tmp, t_utils_pipe *pipe_hand, char ***envp,
		int *exit_running_in[3])
{
	int	is_last;

	is_last = 0;
	init_signals_child();
	if ((sigint_return(&exit_running_in[0])) == 1)
		return ;
	pipe_hand->child_proc = fork();
	if (pipe_hand->child_proc == 0)
	{
		if (tmp->next == NULL)
			is_last = 1;
		child_setup_fds(pipe_hand, *exit_running_in[2], is_last);
		if (build_in_flag(tmp))
		{
			execute_buildin(tmp, envp, exit_running_in);
			free_copy_envp(envp);
			free_list_p(pipe_hand->parser);
			free(pipe_hand);
		}
		else
			execute_fun(tmp, exit_running_in[0], envp, pipe_hand);
		exit(*exit_running_in[0]);
	}
	fork_error(pipe_hand);
	close_fds(tmp, pipe_hand, exit_running_in[2]);
}

int	handle_single_build_in(t_utils_pipe *pipe_hand, t_parser *tmp,
		char ***envp, int *exit_running[2])
{
	int	saved_in;
	int	saved_out;

	if ((pick_redirections(pipe_hand, tmp, exit_running[0], envp)) == 1)
		return (1);
	if (g_signal == SIGINT)
		return (*exit_running[0] = 130);
	saved_in = dup(STDIN_FILENO);
	if (saved_in == -1)
		return (perror("dup stdin"), -1);
	saved_out = dup(STDOUT_FILENO);
	if (saved_out == -1)
		return (perror("dup stdout"), -1);
	check_fd_single_buildin(pipe_hand);
	execute_buildin(tmp, envp, exit_running);
	if (dup2(saved_in, STDIN_FILENO) == -1)
		perror("restore stdin");
	if (dup2(saved_out, STDOUT_FILENO) == -1)
		perror("restore stdout");
	close(saved_in);
	close(saved_out);
	free(pipe_hand);
	return (0);
}

int	handle_other(t_parser *parser, t_utils_pipe *pipe_hand,
	int *exit_running[2], char ***envp)
{
	pid_t			last_pid;
	int				prev_in;
	t_parser		*tmp;

	tmp = parser;
	prev_in = -1;
	while (tmp)
	{
		pipe_hand->fd_in = -1;
		pipe_hand->fd_out = -1;
		if ((pick_redirections(pipe_hand, tmp, exit_running[0], envp)) == 1)
			return (1);
		if (tmp->next)
			init_pipe(pipe_hand->fd);
		init_child_proc(tmp, pipe_hand, envp,
			(int*[3]){exit_running[0], exit_running[1], &prev_in});
		if (tmp->next == NULL)
			last_pid = pipe_hand->child_proc;
		if (pipe_hand->fd_in != -1)
			close(pipe_hand->fd_in);
		if (pipe_hand->fd_out != -1)
			close(pipe_hand->fd_out);
		tmp = tmp->next;
	}
	return (last_cmd_stat(last_pid, exit_running[0]), 0);
}

int	execute_pipes(t_parser **parser, char ***envp, int *running)
{
	t_utils_pipe	*pipe_hand;
	int				exit_stat;

	exit_stat = 0;
	init_cmd(&pipe_hand, parser);
	if (!(*parser))
		return (free(pipe_hand), EXIT_FAILURE);
	if (build_in_flag((*parser)) && (*parser)->next == NULL)
	{
		if ((handle_single_build_in(pipe_hand, (*parser), envp,
					(int *[2]){&exit_stat, running})) == 1)
			return (free_list_p(parser), 1);
		return (exit_stat);
	}
	else
	{
		if ((handle_other((*parser), pipe_hand, (int *[2])
					{&exit_stat, running}, envp)) == 1)
			return (free_list_p(parser), 1);
	}
	sig_stat(&exit_stat);
	init_signals();
	return (free(pipe_hand), exit_stat);
}
