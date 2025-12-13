/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:17:14 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/12 18:40:03 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	execute_fun(t_parser *tmp, int *exit_stat,
	char ***envp, t_utils_pipe *pipe_hand)
{
	char	**path;

	path = x_path(*envp, tmp->words[0], exit_stat, pipe_hand);
	if (!path)
		exit(*exit_stat);
	if (execve(*path, tmp->words, *envp) == -1)
	{
		perror("Is a directory");
		*exit_stat = 126;
		free_copy_envp(envp);
		free_list_p(pipe_hand->parser);
		free(pipe_hand);
		free_copy_envp(&path);
		exit(*exit_stat);
	}
}
