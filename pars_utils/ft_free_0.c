/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:45:57 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 11:23:04 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all_envt(t_envt **envt)
{
	t_envt	*tmp;

	if (!envt)
		return ;
	while (*envt)
	{
		tmp = (*envt)->next;
		free((*envt)->name);
		free((*envt)->value);
		free(*envt);
		*envt = tmp;
	}
}

static size_t	size_str(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_all_rds(t_rds **rds)
{
	t_rds	*tmp;

	if (!rds)
		return ;
	while (*rds)
	{
		tmp = (*rds)->next;
		free_str(size_str((*rds)->rd), (*rds)->rd);
		free(*rds);
		*rds = NULL;
		*rds = tmp;
	}
	*rds = NULL;
}

void	free_all_toexec(t_toexec **toexec)
{
	t_toexec	*tmp;

	if (!toexec)
		return ;
	while (*toexec)
	{
		tmp = (*toexec)->next;
		if ((*toexec)->cmd)
			free_str(size_str((*toexec)->cmd), (*toexec)->cmd);
		if ((*toexec)->rds)
			free_all_rds(&(*toexec)->rds);
		free(*toexec);
		*toexec = tmp;
	}
	*toexec = NULL;
}

void	free_str(size_t i, char **str)
{
	while (i > 0)
	{
		i--;
		free(str[i]);
	}
	free(str);
}
