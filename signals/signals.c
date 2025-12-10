/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:23:38 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/10 17:39:27 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

volatile sig_atomic_t	g_signal = 0;

int	event(void)
{
	return (0);
}

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

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signals_child(void)
{
	signal(SIGINT, signal_handler_child);
	signal(SIGQUIT, signal_handler_child);
}

void	init_signals_heredoc(void)
{
	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
