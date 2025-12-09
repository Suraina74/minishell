/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:52:23 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/09 17:00:19 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	miniloop(int *exit_stat, char ***envp_new)
{
	int			running;
	char		*rl;
	t_parser	*parser_list;

	running = true;
	while (running)
	{
		init_signals();
		g_signal = 0;
		parser_list = NULL;
		rl = readline("minishell > ");
		if (rl == NULL)
			break ;
		if ((check_input(rl)) == 1)
			parser_list = NULL;
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
