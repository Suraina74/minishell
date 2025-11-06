/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:15:56 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/06 17:52:32 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int execute_buildin(t_parser *parser_list, char **envp)
{
	t_parser	*tmp;

	tmp = parser_list;
	if ((ft_strncmp(tmp->words[0], "echo", 4)) == 0)
		return (build_in_echo(tmp->words));
	else if ((ft_strncmp(tmp->words[0], "cd", 2)) == 0)
		return (build_in_cd(tmp->words));
	else if ((ft_strncmp(tmp->words[0], "pwd", 3)) == 0)
		return (build_in_pwd());
	else if ((ft_strncmp(tmp->words[0], "export", 6)) == 0)
		envp = build_in_export(tmp, envp);
	else if ((ft_strncmp(tmp->words[0], "unset", 5)) == 0)
		return (printf("unset goes here!\n"));
	else if ((ft_strncmp(tmp->words[0], "env", 3)) == 0)
		return (build_in_env(envp));
	else if ((ft_strncmp(tmp->words[0], "exit", 4)) == 0)
		return (build_in_exit(tmp));
	return (0);
}

int	build_in_flag(t_parser *parser_list)
{
	t_parser	*tmp;

	tmp = parser_list;
	if ((ft_strncmp(tmp->words[0], "echo", 4)) == 0)
		return (1);
	else if ((ft_strncmp(tmp->words[0], "cd", 2)) == 0)
		return (1);
	else if ((ft_strncmp(tmp->words[0], "pwd", 3)) == 0)
		return (1);
	else if ((ft_strncmp(tmp->words[0], "export", 6)) == 0)
		return (1);
	else if ((ft_strncmp(tmp->words[0], "unset", 5)) == 0)
		return (1);
	else if ((ft_strncmp(tmp->words[0], "env", 3)) == 0)
		return (1);
	else if ((ft_strncmp(tmp->words[0], "exit", 4)) == 0)
		return (1);
	return (0);
}
