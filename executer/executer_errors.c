/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:39:27 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/12 17:45:44 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	path_error(char ***envp, char *command, t_utils_pipe **pipe_hand)
{
	ft_putstr_fd("Command not found: ", 2);
	ft_putendl_fd(command, 2);
	free_copy_envp(envp);
	free_list_p((*pipe_hand)->parser);
}

void	fork_error(t_utils_pipe *pipe_hand)
{
	if (pipe_hand->child_proc < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	path_error_two(char *command, char ***envp,
		t_utils_pipe **pipe_hand, char ***commands)
{
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": No such file or directory", 2);
	free_copy_envp(envp);
	free_list_p((*pipe_hand)->parser);
	free_copy_envp(commands);
	free(*pipe_hand);
}
