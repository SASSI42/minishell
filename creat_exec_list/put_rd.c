/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_rd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:53:07 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/12 16:45:43 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nbr_arg(t_words **words)
{
	t_words	*tmp;
	int		i;

	i = 0;
	tmp = *words;
	while (tmp && tmp->type != APPEND && tmp->type != IN_RED
		&& tmp->type != OUT_RED && tmp->type != HEREDOC && tmp->type != PIPE)
	{
		if (tmp->type == FILE_IN || tmp->type == FILE_OUT
			|| tmp->type == APPEND_F || tmp->type == HEREDOC_E
			|| tmp->type == HEREDOC_O)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static t_rds	*find_l_node(t_rds *last)
{
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

static int	put_rd(t_rds **rds, t_words **words)
{
	t_rds	*node;
	t_rds	*l_node;

	if (!rds)
		return (-1);
	node = malloc(sizeof(t_rds));
	if (!node)
		return (ft_putstr_fd("minishell: error malloc", 2)
			, free_all_rds(rds), (*words)->main->exit_status = 1, -1);
	node->next = NULL;
	if (put_file_rd(node, words, nbr_arg(&(*words)->next) + 1) == -1)
		return (free(node), free_all_rds(rds), -1);
	if (!(*rds))
		*rds = node;
	else
	{
		l_node = find_l_node(*rds);
		l_node->next = node;
	}
	return (0);
}

static int	put_rds(t_toexec *toexec, t_words **words)
{
	t_words		*tmp;

	tmp = *words;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == APPEND || tmp->type == IN_RED
			|| tmp->type == OUT_RED || tmp->type == HEREDOC)
			if (put_rd(&toexec->rds, &tmp) == -1)
				return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	put_rd_toexec(t_words **words, t_toexec **toexec)
{
	t_toexec	*tmp_exec_0;
	t_words		*tmp_rd_0;

	tmp_exec_0 = *toexec;
	tmp_rd_0 = *words;
	while (tmp_exec_0)
	{
		tmp_exec_0->rds = NULL;
		if (tmp_rd_0 && tmp_rd_0->type == PIPE)
			tmp_rd_0 = tmp_rd_0->next;
		if (put_rds(tmp_exec_0, &tmp_rd_0) == -1)
			return (-1);
		while (tmp_rd_0 && tmp_rd_0->type != PIPE)
			tmp_rd_0 = tmp_rd_0->next;
		tmp_exec_0 = tmp_exec_0->next;
	}
	return (0);
}
