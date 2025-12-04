/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:17:14 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/04 17:58:20 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	execute_fun(t_parser *tmp, int *exit_stat, char ***envp)
{
	char	**path;

	path = x_path(*envp, tmp->words[0], exit_stat);
	if (!path)
		exit(*exit_stat);
	if (execve(*path, tmp->words, *envp) == -1)
	{
		perror("execve");
		free(path);
		exit(*exit_stat);
	}
}
