/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:32:57 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/03 13:53:32 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	init_cmd(t_utils_pipe **cmd_struct)
{
	t_utils_pipe	*tmp;

	tmp = malloc(sizeof(t_utils_pipe));
	if (!tmp)
		return ;
	tmp->command = NULL;
	tmp->fd_in = -1;
	tmp->fd_out = -1;
	tmp->child_proc = -1;
	*cmd_struct = tmp;
}

void	init_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	ft_free_path(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

void	set_stat(int *exit_stat, char *command, char *full_path)
{
	if ((access(full_path, X_OK) == -1) || (access(full_path, F_OK) == -1))
	{
		ft_putstr_fd(command, 2);
		if ((access(full_path, X_OK) == -1))
		{
			ft_putendl_fd(": Permission denied", 2);
			*exit_stat = 126;
		}
		if ((access(full_path, F_OK) == -1))
		{
			ft_putendl_fd(": command not found", 2);
			*exit_stat = 127;
		}
		exit(*exit_stat);
	}
}
