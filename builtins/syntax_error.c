/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:31:54 by msassi            #+#    #+#             */
/*   Updated: 2024/06/12 20:32:22 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_syntax_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '=' || str[i] == '+') && i == 0)
			return (-1);
		if (str[i] == '=')
			return (0);
		if (i == 0 && ft_isdigit(str[i]) == 1)
			return (-1);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_'
			&& !(str[i] == '+' && str[i + 1] == '='))
			return (-1);
		i++;
	}
	return (0);
}

t_envt	*name_search(char *name, t_envt *envt)
{
	while (envt != NULL)
	{
		if (ft_strcmp(name, envt->name) == 0)
			return (envt);
		envt = envt->next;
	}
	return (NULL);
}
