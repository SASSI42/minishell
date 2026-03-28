/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:13:17 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 23:34:10 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_main(t_shell *main)
{
	clear_pid(&main->pid);
	rl_clear_history();
	close(main->pipein);
	restore_std(main, -1),
	free_all_envt(&main->envt);
	free_list_toexec(&main->toexec);
}

void	free_all_words(t_words **words)
{
	t_words	*tmp;

	if (!words)
		return ;
	while (*words)
	{
		tmp = (*words)->next;
		free((*words)->word);
		(*words)->word = NULL;
		free(*words);
		*words = NULL;
		*words = tmp;
	}
}

void	free_list_toexec(t_toexec **toexec)
{
	t_toexec	*tmp;

	if (!toexec)
		return ;
	while (*toexec)
	{
		if ((*toexec)->input != 0)
			close((*toexec)->input);
		if ((*toexec)->rds)
			free_all_rds(&(*toexec)->rds);
		tmp = (*toexec)->next;
		free(*toexec);
		*toexec = tmp;
	}
	*toexec = NULL;
}

void	next_cmd(t_shell *main, t_toexec **toexec)
{
	t_toexec	*tmp_toexec;

	tmp_toexec = *toexec;
	while (tmp_toexec)
	{
		if (tmp_toexec->input != 0)
			close(tmp_toexec->input);
		tmp_toexec = tmp_toexec->next;
	}
	free_all_toexec(&main->toexec);
}
