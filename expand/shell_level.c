/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:20:17 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 11:19:08 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_value(char *env_line)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	if (env_line[i] == '\0')
		return (NULL);
	i++;
	if (env_line[i] == '\0' && i != 0 && env_line[i - 1] == '=')
		return (ft_strdup(""));
	if (env_line[i] == '\0')
		return (NULL);
	value = malloc(sizeof(char) * (ft_strlen(env_line) - i + 1));
	if (!value)
		return (func_error("memory allocation"), NULL);
	while (env_line[i])
	{
		value[j] = env_line[i];
		j++;
		i++;
	}
	return (value[j] = '\0', value);
}

char	*ft_name(char *env_line)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env_line[i] && env_line[i] != '=' && env_line[i] != '+')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (func_error("memory allocation"), NULL);
	while (j < i)
	{
		name[j] = env_line[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}

static int	adjust_shelvl(t_envt *shelvl, char *value, int i)
{
	if (i == 1000)
	{
		value = ft_strdup("");
		if (value == NULL)
			return (-1);
		free(shelvl->value);
		shelvl->value = value;
		return (0);
	}
	else if (i > 1000)
	{
		(ft_error("minishell: warning: shell level ("), ft_error(ft_itoa(i)));
		(ft_error(") too high, resetting to 1\n"), i = 1);
	}
	else if (i < 0)
		i = 0;
	value = ft_itoa(i);
	if (value == NULL)
		return (-1);
	free(shelvl->value);
	shelvl->value = value;
	return (0);
}

int	shell_level(t_envt **envt, char *name, char *value, t_envt *shelvl)
{
	long	num;

	if (shelvl == NULL || shelvl->value == NULL)
	{
		value = ft_strdup("1");
		if (value == NULL)
			return (-1);
		if (shelvl != NULL && shelvl->value == NULL)
			return (shelvl->value = value, 0);
		name = ft_strdup("SHLVL");
		if (name == NULL)
			return (free(value), -1);
		if (add_env_node(name, value, envt) == 1)
			return (-1);
		return (0);
	}
	if (ft_atoi(shelvl->value, &num) == -1)
	{
		value = ft_strdup("1");
		if (value == NULL)
			return (-1);
		shelvl->value = value;
		return (0);
	}
	return (adjust_shelvl(shelvl, NULL, (int)num + 1));
}
