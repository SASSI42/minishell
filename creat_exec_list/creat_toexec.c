/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_toexec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:18:11 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/12 16:59:27 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_toexec	*find_l_nodeexec(t_toexec *last)
{
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

static int	new_add_node(t_toexec **toexec, t_shell *main)
{
	t_toexec	*node;
	t_toexec	*l_node;

	if (!toexec)
		return (1);
	node = malloc(sizeof(t_toexec));
	if (!node)
		return (ft_putstr_fd("minishell: error malloc", 2)
			, free_all_toexec(toexec), main->exit_status = 1, 1);
	node->rds = NULL;
	node->cmd = NULL;
	node->next = NULL;
	node->prev = NULL;
	if (!(*toexec))
		*toexec = node;
	else
	{
		l_node = find_l_nodeexec(*toexec);
		l_node->next = node;
		node->prev = l_node;
	}
	return (0);
}

static int	creat_node(t_shell *main)
{
	t_words	*tmp_words;

	tmp_words = main->words;
	while (tmp_words)
	{
		if (tmp_words->index == 0)
		{
			if (new_add_node(&main->toexec, main))
				return (-1);
		}
		tmp_words = tmp_words->next;
	}
	return (0);
}

int	creat_toexec(t_shell *main)
{
	main->toexec = NULL;
	if (creat_node(main) == -1)
		return (-1);
	main->toexec->envt = main->envt;
	main->toexec->cmd = NULL;
	if (set_put_fd(&main->words, &main->toexec, main) == -1)
		return (free_list_toexec(&main->toexec), -1);
	if (put_rd_toexec(&main->words, &main->toexec) == -1)
		return (free_list_toexec(&main->toexec), -1);
	if (put_cmd_toexec(&main->words, &main->toexec) == -1)
		return (free_list_toexec(&main->toexec), -1);
	return (0);
}
