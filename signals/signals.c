/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:23:38 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/13 11:14:01 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

volatile sig_atomic_t	g_signal = 0;

void	signal_handler_child(int signal)
{
	g_signal = signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signal_handler_heredoc(int signal)
{
	g_signal = signal;
	rl_done = 1;
}

void	signal_handler(int signal)
{
	g_signal = signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	sigint_return(int *exit_running_in[0])
{
	if (g_signal == SIGINT)
	{
		*exit_running_in[0] = 130;
		return (1);
	}
	return (0);
}
