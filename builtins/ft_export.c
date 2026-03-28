/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:37:33 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 17:06:16 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	append_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (str[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

static int	append_to_variable(char *name, char *value, t_envt **envt)
{
	t_envt	*tmp;
	char	*ptr;

	tmp = name_search(name, *envt);
	if (tmp == NULL)
	{
		if (add_env_node(name, value, envt) != 0)
			return (1);
		return (0);
	}
	if (value[0] == '\0')
		return (free(value), free(name), 0);
	ptr = tmp->value;
	tmp->value = ft_strjoin(tmp->value, value);
	free(ptr);
	free(value);
	if (tmp->value == NULL)
		return (free(name), -1);
	return (free(name), 0);
}

static int	allocate_variable(t_envt **envt, char **cmd, int i)
{
	char	*name;
	char	*value;

	name = ft_name(cmd[i]);
	if (name == NULL)
		return (1);
	value = ft_value(cmd[i]);
	if (value == NULL && name_search(name, *envt) != NULL)
		return (free(name), 0);
	if (name_search(name, *envt) != NULL)
		remove_variable(name, envt);
	if (add_env_node(name, value, envt) == 1)
		return (1);
	return (0);
}

static int	add_variable(char **cmd, t_envt **envt, int i, int err)
{
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i], "_") == 0)
		{
			i++;
			continue ;
		}
		if (export_syntax_error(cmd[i]) == -1)
		{
			(ft_error("minishell: export: `"), ft_error(cmd[i]),
				ft_error("': not a valid identifier\n"), err = 1);
			i++;
			continue ;
		}
		if (append_check(cmd[i]) == 1)
			append_to_variable(ft_name(cmd[i]), ft_value(cmd[i]), envt);
		else
		{
			if (allocate_variable(envt, cmd, i) == 1)
				return (1);
		}
		i++;
	}
	return (err);
}

int	ft_export(char **cmd, t_envt **envt)
{
	t_envt	*tmp;

	tmp = *envt;
	if (cmd[1] == NULL)
	{
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->name, "_") != 0)
			{
				if (tmp->value != NULL)
					printf("declare -x %s=\"%s\"\n",
						tmp->name, tmp->value);
				else
					printf("declare -x %s\n", tmp->name);
			}
			tmp = tmp->next;
		}
	}
	else
	{
		if (add_variable(cmd, envt, 1, 0) == 1)
			return (1);
	}
	return (0);
}
