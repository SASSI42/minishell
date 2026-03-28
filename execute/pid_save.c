/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:56:40 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 23:33:20 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_pid(t_pid **pid)
{
	t_pid	*tmp;
	t_pid	*prev;

	if (pid == NULL || *pid == NULL)
		return ;
	tmp = *pid;
	while (tmp != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	*pid = NULL;
}

int	add_pid(t_pid **node, t_pid *new)
{
	t_pid	*tmp;

	if (new == NULL)
		return (-1);
	if (*node == NULL)
	{
		*node = new;
		return (0);
	}
	tmp = *node;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	return (0);
}

t_pid	*new_pid(int pid)
{
	t_pid	*node;

	node = malloc(sizeof(t_pid));
	if (node == NULL)
		return (func_error("memory allocation"), NULL);
	node->pid = pid;
	node->next = NULL;
	return (node);
}
