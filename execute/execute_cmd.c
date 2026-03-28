/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:24:05 by msassi            #+#    #+#             */
/*   Updated: 2024/06/12 22:55:18 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_env_len(t_envt *envt)
{
	int	len;
	int	i;

	i = 0;
	while (envt->name[i] != '\0')
		i++;
	len = i + 1;
	i = 0;
	while (envt->value[i] != '\0')
		i++;
	len += i;
	return (len);
}

static void	env_copy(t_envt *envt, char *env)
{
	int	i;
	int	a;

	i = 0;
	while (envt->name[i] != '\0')
	{
		env[i] = envt->name[i];
		i++;
	}
	env[i] = '=';
	i++;
	a = 0;
	while (envt->value[a] != '\0')
	{
		env[i] = envt->value[a];
		i++;
		a++;
	}
	env[i] = '\0';
}

static char	**get_env(t_envt *envt, int n, int i)
{
	t_envt	*tmp;
	char	**env;

	tmp = envt;
	while (envt != NULL)
	{
		if (envt->value != NULL)
			n++;
		envt = envt->next;
	}
	envt = tmp;
	env = malloc((n + 1) * sizeof(char *));
	while (envt != NULL)
	{
		if (envt->value != NULL)
		{
			env[i] = malloc(get_env_len(envt) + 1);
			env_copy(envt, env[i]);
			i++;
		}
		envt = envt->next;
	}
	env[i] = NULL;
	return (env);
}

static int	is_a_directory(char *cmd)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (cmd[i] != '\0')
	{
		if (c > 2)
			return (0);
		if (cmd[i] != '/' && cmd[i] != '.')
			return (0);
		if (cmd[i] == '.')
			c++;
		if (cmd[i] == '/')
			c = 0;
		i++;
	}
	ft_error("minishell: ");
	ft_error(cmd);
	ft_error(": is a directory\n");
	return (1);
}

void	execute_cmd(t_shell *main, t_toexec *node, t_envt *envt)
{
	char	*path;
	char	**cmd;
	char	**env;

	cmd = node->cmd;
	if (cmd == NULL || cmd[0] == NULL)
		(close(0), close(1), exit(0));
	if (cmd[0][0] == '\0')
		(cmd_error(cmd[0]), close(0), close(1), exit(127));
	if (is_a_directory(cmd[0]) == 1)
		(close(0), close(1), exit(126));
	path = find_path(main->paths, cmd[0]);
	if (path == NULL)
		(cmd_error(cmd[0]), close(0), close(1), exit(127));
	env = get_env(envt, 0, 0);
	if (env == NULL)
		(close(0), close(1), free(path), exit(1));
	execve(path, cmd, env);
	(close(0), close(1), free(path), ft_free(env));
	(ft_error("minishell: "), perror(cmd[0]), exit(126));
}
