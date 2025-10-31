/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:15:56 by ksoedama          #+#    #+#             */
/*   Updated: 2025/10/30 16:58:01 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char **check_if_buildin(t_parser *parser_list, char **envp)
{
	size_t		i;
	t_parser	*tmp;

	i = 0;
	tmp = parser_list;
	while (tmp)
	{
		i = 0;
		while (tmp->words[i])
		{
			if ((ft_strncmp(tmp->words[i], "echo", 4)) == 0)
				build_in_echo(tmp->words);
			else if ((ft_strncmp(tmp->words[i], "cd", 2)) == 0)
				build_in_cd(tmp->words);
			else if ((ft_strncmp(tmp->words[i], "pwd", 3)) == 0)
				build_in_pwd();
			else if ((ft_strncmp(tmp->words[i], "export", 6)) == 0)
				envp = build_in_export(tmp, envp);
			else if ((ft_strncmp(tmp->words[i], "unset", 5)) == 0)
				printf("unset goes here!\n");
			else if ((ft_strncmp(tmp->words[i], "env", 3)) == 0)
				build_in_env(envp);
			else if ((ft_strncmp(tmp->words[i], "exit", 4)) == 0)
				build_in_exit(tmp);
			i++;
		}
		break ;
		tmp = tmp->next;
	}
	return (envp);
}

int	build_in_flag(t_parser *parser_list)
{
	size_t i;
	t_parser *tmp;

	i = 0;
	tmp = parser_list;
	while (tmp)
	{
		i = 0;
		while (tmp->words[i])
		{
			if ((ft_strncmp(tmp->words[i], "echo", 4)) == 0)
				return (1);
			else if ((ft_strncmp(tmp->words[i], "cd", 2)) == 0)
				return (1);
			else if ((ft_strncmp(tmp->words[i], "pwd", 3)) == 0)
				return (1);
			else if ((ft_strncmp(tmp->words[i], "export", 6)) == 0)
				return (1);
			else if ((ft_strncmp(tmp->words[i], "unset", 5)) == 0)
				return (1);
			else if ((ft_strncmp(tmp->words[i], "env", 3)) == 0)
				return (1);
			else if ((ft_strncmp(tmp->words[i], "exit", 4)) == 0)
				return (1);
			i++;
		}
		break ;
		tmp = tmp->next;
	}
	return (0);
}
