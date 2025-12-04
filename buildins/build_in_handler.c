/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:15:56 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/04 15:40:08 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	execute_buildin(t_parser *parser_list, char ***envp, int *running)
{
	t_parser	*tmp;
	int			exit_stat;

	exit_stat = 0;
	tmp = parser_list;
	if (tmp->words[0] == NULL)
		return (1);
	else if ((ft_strncmp(tmp->words[0], "echo", 4)) == 0)
		return (build_in_echo(tmp->words));
	else if ((ft_strncmp(tmp->words[0], "cd", 2)) == 0)
		return (build_in_cd(tmp->words));
	else if ((ft_strncmp(tmp->words[0], "pwd", 3)) == 0)
		return (build_in_pwd());
	else if ((ft_strncmp(tmp->words[0], "export", 6)) == 0)
		return (build_in_export(tmp, envp));
	else if ((ft_strncmp(tmp->words[0], "unset", 5)) == 0)
		return (build_in_unset(tmp, envp));
	else if ((ft_strncmp(tmp->words[0], "env", 3)) == 0)
		return (build_in_env(envp));
	else if ((ft_strncmp(tmp->words[0], "exit", 4)) == 0)
		return (build_in_exit(exit_stat, tmp, running));
	return (0);
}

int	build_in_flag(t_parser *parser_list)
{
	t_parser	*tmp;
	int			len;

	tmp = parser_list;
	if (tmp->words[0] == NULL)
		return (1);
	len = ft_strlen(tmp->words[0]);
	if ((ft_strncmp(tmp->words[0], "echo", 4)) == 0 && (len == 4))
		return (1);
	else if ((ft_strncmp(tmp->words[0], "cd", 2)) == 0 && (len == 2))
		return (1);
	else if ((ft_strncmp(tmp->words[0], "pwd", 3)) == 0 && (len == 3))
		return (1);
	else if ((ft_strncmp(tmp->words[0], "export", 6)) == 0 && (len == 6))
		return (1);
	else if ((ft_strncmp(tmp->words[0], "unset", 5)) == 0 && (len == 5))
		return (1);
	else if ((ft_strncmp(tmp->words[0], "env", 3)) == 0 && (len == 3))
		return (1);
	else if ((ft_strncmp(tmp->words[0], "exit", 4)) == 0 && (len == 4))
		return (1);
	return (0);
}
