/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:23:38 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/06 16:26:10 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

sig_atomic_t g_signal = 0;

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
	write(1, "\n", 1);
	// close(STDIN_FILENO);
	rl_done = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signal_handler(int signal)
{
	g_signal = signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signals_child()
{
	signal(SIGINT, signal_handler_child);
	signal(SIGQUIT, signal_handler_child);
}

void	init_signals_heredoc()
{
	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
