/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:42:57 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/14 11:03:30 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigv;

static int	set_main(t_shell *main, int i)
{
	if (i == 0)
	{
		main->exit_status = 0;
		main->words = NULL;
		main->toexec = NULL;
		main->envt = NULL;
		main->pid = NULL;
		main->pipein = -1;
		return (dup_std(main));
	}
	else if (i == 1)
	{
		main->s_error = 0;
		main->s_export = 0;
		main->s_rd = 0;
	}
	return (0);
}

static int	redirect_line(t_shell *main)
{
	add_history(main->line);
	if (main->line && !ft_pars(main))
	{
		g_sigv = -1;
		if (loop_on_cmd(main, main->toexec) != 0)
			return (1);
		g_sigv = 0;
		next_cmd(main, &main->toexec);
	}
	return (0);
}

static int	minishell(t_shell *main)
{
	while (1)
	{
		reset_terminal(&main->termios, 1);
		set_main(main, 1);
		main->line = readline ("minishell-$ ");
		if (!main->line && !g_sigv)
			(ft_error("exit\n"), restore_std(main, -1),
				free_all_envt(&main->envt), rl_clear_history(), exit(0));
		else if (!main->line && g_sigv == 1)
		{
			main->exit_status = 1;
			restore_std(main, 0);
			g_sigv = 0;
			continue ;
		}
		else if (main->line[0] == '\0')
		{
			free(main->line);
			continue ;
		}
		if (redirect_line(main) != 0)
			return (1);
	}
	return (0);
}

int	reset_terminal(t_termios *termios, int flag)
{
	if (flag == 0)
	{
		if (tcgetattr(STDIN_FILENO, termios) != 0)
			return (perror(""), 1);
		termios->c_lflag &= ~ECHOCTL;
		return (0);
	}
	if (tcsetattr(STDIN_FILENO, TCSANOW, termios) != 0)
		return (perror(""), 1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_shell	main;

	(void)av;
	(void)ac;
	if (isatty(0) == 0)
		return (ft_error("the program only reads from a terminal\n"), 1);
	if (reset_terminal(&main.termios, 0) != 0)
		return (1);
	ft_signal();
	if (set_main(&main, 0) != 0)
		return (1);
	if (put_env(env, &main.envt, -1) == 1)
		return (free_all_envt(&main.envt), 1);
	minishell(&main);
	return (0);
}
