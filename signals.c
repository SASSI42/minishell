/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:41:31 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 23:22:50 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sigv;

void	signal_handler(int sig)
{
	if (sig == SIGINT && g_sigv != -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		g_sigv = 1;
		close (0);
	}
}

void	ft_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
