/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:17:14 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/08 14:56:55 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	execute_fun(t_parser *tmp, char ***envp)
{
	char	**path;

	path = x_path(*envp, tmp->words[0]);
	if (execve(*path, tmp->words, *envp) == -1)
		perror("execve");
}
