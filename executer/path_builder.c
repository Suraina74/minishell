/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:29:27 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/03 17:45:26 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

size_t	longest_dir(char **paths)
{
	size_t	dir;
	size_t	dir_len;

	dir = 0;
	dir_len = 0;
	while (paths[dir])
	{
		if (dir_len < ft_strlen(paths[dir]))
			dir_len = ft_strlen(paths[dir]);
		dir++;
	}
	return (dir_len);
}

static char	*is_path(char **envp)
{
	size_t	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		if (!envp[i])
			exit(EXIT_FAILURE);
		i++;
	}
	return (NULL);
}

static char	*mk_x_path(char **paths, char *command, size_t dir_len)
{
	char	*buffer;
	size_t	dir;

	buffer = malloc((dir_len + ft_strlen(command) + 2) * sizeof(char));
	dir = 0;
	if (buffer)
	{
		while (paths[dir])
		{
			ft_strlcpy(buffer, paths[dir], dir_len + ft_strlen(command) + 2);
			ft_strlcat(buffer, "/", dir_len + ft_strlen(command) + 2);
			ft_strlcat(buffer, command, dir_len + ft_strlen(command) + 2);
			if (access(buffer, X_OK) == 0)
				return (buffer);
			dir++;
		}
	}
	free(buffer);
	return (NULL);
}

static char	*get_full_path(char **envp, char *command, int *exit_stat)
{
	char	**paths;
	char	*path_variable;
	char	*full_path;
	size_t	dir_len;

	path_variable = is_path(envp);
	if (!path_variable)
		exit(EXIT_FAILURE);
	paths = ft_split(path_variable, ':');
	if (!paths)
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		full_path = ft_strdup(command);
		return (ft_free_path(paths), full_path);
	}
	dir_len = longest_dir(paths);
	full_path = mk_x_path(paths, command, dir_len);
	if (!full_path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(command, 2);
		*exit_stat = 127;
	}
	return (ft_free_path(paths), full_path);
}

char	**x_path(char **envp, char *command, int *exit_stat)
{
	char	**result;
	char	*full_path;

	if (command[0] == ' ' || command[0] == '\0')
	{
		ft_putstr_fd(command, 2);
		ft_putendl_fd(": command not found", 2);
		*exit_stat = 127;
	}
	result = ft_split(command, ' ');
	if (result == NULL || result[0] == NULL)
		return (free(result), NULL);
	full_path = get_full_path(envp, result[0], exit_stat);
	if (full_path == NULL)
		return (ft_free_path(result), NULL);
	set_stat(exit_stat, command, full_path);
	free(result[0]);
	result[0] = full_path;
	return (result);
}
