/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:24:19 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/16 12:24:18 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	build_in_env(char **words, char ***envp, int *exit_stat)
{
	int		i;
	char	*current;

	i = 0;
	if (words[0] && words[1])
		return (ft_putendl_fd("No such file or directory", 2), \
*exit_stat = 127);
	while ((*envp)[i])
	{
		current = ft_strchr((*envp)[i], '=');
		if (current && *current + 1 != '\0')
			printf("%s\n", (*envp)[i]);
		i++;
	}
	return (*exit_stat = 0);
}
