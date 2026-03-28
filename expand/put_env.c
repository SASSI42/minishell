/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:56:23 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 11:20:59 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envt	*find_l_node_0(t_envt *last)
{
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

int	add_env_node(char *name, char *value, t_envt **envt)
{
	t_envt	*node;
	t_envt	*l_node;

	if (!name)
		return (free(value), 1);
	node = malloc(sizeof(t_envt));
	if (!node)
	{
		(free(name), free(value));
		(free_all_envt(envt), *envt = NULL);
		return (func_error("memory allocation"), 1);
	}
	node->name = name;
	node->next = NULL;
	node->value = value;
	if (!(*envt))
		*envt = node;
	else
	{
		l_node = find_l_node_0(*envt);
		l_node->next = node;
	}
	return (0);
}

static int	add_path(t_envt **envt)
{
	t_envt	*path;
	char	*name;
	char	*value;

	path = name_search("PATH", *envt);
	if (path == NULL)
	{
		name = ft_strdup("PATH");
		if (name == NULL)
			return (-1);
		value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		if (name == NULL)
			return (free(name), -1);
		if (add_env_node(name, value, envt) == 1)
			return (-1);
	}
	return (0);
}

int	put_env(char **env, t_envt **envt, int i)
{
	char	*name;
	char	*value;

	while (env[++i])
	{
		if (add_env_node(ft_name(env[i]), ft_value(env[i]), envt) == 1)
			return (-1);
	}
	(remove_variable("OLDPWD", envt), remove_variable("PWD", envt));
	name = ft_strdup("PWD");
	if (name == NULL)
		return (-1);
	value = getcwd(NULL, 0);
	if (value == NULL)
		return (free(name), -1);
	if (add_env_node(name, value, envt) == 1)
		return (-1);
	name = ft_strdup("OLDPWD");
	if (name == NULL)
		return (-1);
	if (add_env_node(name, NULL, envt) == 1)
		return (-1);
	if (shell_level(envt, name, value, name_search("SHLVL", *envt)) == -1)
		return (-1);
	return (add_path(envt));
}
