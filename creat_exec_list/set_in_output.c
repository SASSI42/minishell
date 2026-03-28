/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:53:34 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 12:44:35 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sigv;

static int	open_file(t_words *words, t_toexec *toexec, t_shell *main)
{
	int	i;

	i = 0;
	if (words->type == HEREDOC_E || words->type == HEREDOC_O)
	{
		if (toexec->input != 0)
			close (toexec->input);
		i = open_heredoc(words, toexec, main);
		if (i == -1)
			return (-1);
	}
	return (0);
}

static void	set_in_out(t_toexec *toexec)
{
	toexec->input = 0;
	toexec->output = 1;
}

int	set_put_fd(t_words **words, t_toexec **toexec, t_shell *main)
{
	t_words		*tmp;
	t_toexec	*tmp_exec;

	tmp = *words;
	tmp_exec = *toexec;
	while (tmp_exec)
	{
		set_in_out(tmp_exec);
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		while (tmp && tmp->type != PIPE)
		{
			if (tmp_exec->input != -1 && tmp_exec->output != -1 && g_sigv == 0)
				if (open_file(tmp, tmp_exec, main) == -1)
					break ;
			tmp = tmp->next;
		}
		tmp_exec = tmp_exec->next;
	}
	if (g_sigv == 1)
		return (main->exit_status = 1, restore_std(main, 0), g_sigv = 0, -1);
	return (restore_std(main, 0), 0);
}
