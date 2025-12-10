/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:52:23 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/10 17:30:55 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*prompt(t_parser **parser_list, int *exit_stat)
{
	char	*line;

	g_signal = 0;
	init_signals();
	*parser_list = NULL;
	line = readline("minishell > ");
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		*exit_stat = 130;
	}
	return (line);
}

void	miniloop(int *exit_stat, char ***envp_new)
{
	int			running;
	char		*rl;
	t_parser	*parser_list;

	running = true;
	while (running)
	{
		rl = prompt(&parser_list, exit_stat);
		if (rl == NULL)
			break ;
		else if ((parsing(&parser_list, rl, *envp_new, *exit_stat)) == 1)
		{
			free_copy_envp(envp_new);
			free(rl);
			return ;
		}
		*exit_stat = execute_pipes(&parser_list, envp_new, &running);
		if (rl[0] != '\0')
			add_history(rl);
		free(rl);
		free_list_p(&parser_list);
	}
}
