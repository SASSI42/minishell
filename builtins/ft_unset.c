/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:39:17 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 17:07:42 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_syntax_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && ft_isdigit(str[i]) == 1)
			return (-1);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

int	remove_variable(char *name, t_envt **envt)
{
	t_envt	*head;
	t_envt	*prev;

	head = *envt;
	prev = NULL;
	while ((*envt) != NULL)
	{
		if (ft_strcmp(name, (*envt)->name) == 0)
			break ;
		prev = *envt;
		*envt = (*envt)->next;
	}
	if (*envt != NULL)
	{
		if (prev != NULL)
			prev->next = (*envt)->next;
		else
			head = (*envt)->next;
		free((*envt)->name);
		free((*envt)->value);
		free(*envt);
	}
	*envt = head;
	return (0);
}

int	ft_unset(char **cmd, t_envt **envt)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i], "_") == 0)
		{
			i++;
			continue ;
		}
		if (unset_syntax_error(cmd[i]) == -1)
			(ft_error("minishell: unset: `"), ft_error(cmd[i]),
				ft_error("': not a valid identifier\n"), err = 1);
		remove_variable(cmd[i], envt);
		i++;
	}
	return (err);
}
