/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:47:16 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 18:14:12 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_cmd(char *path, char *cmd)
{
	char	*arr;
	int		i;
	int		j;

	i = -1;
	j = ft_strlen(cmd) + ft_strlen(path) + 1;
	arr = malloc(j + 1);
	if (arr == NULL)
		return (func_error("malloc"), NULL);
	j = 0;
	while (path[++i] != '\0')
		arr[i] = path[i];
	arr[i++] = '/';
	while (cmd[j] != '\0')
	{
		arr[i] = cmd[j];
		i++;
		j++;
	}
	arr[i] = '\0';
	if (access(arr, X_OK) == 0)
		return (arr);
	else
		return (NULL);
}

char	*find_path(char **paths, char *cmd)
{
	char	*path;
	int		j;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	if (paths == NULL || *paths == NULL)
		(ft_error("mininshell: "), perror(cmd), close(0), close(1), exit(127));
	if (cmd[0] == '.' || cmd[0] == '/')
		return (NULL);
	j = -1;
	while (paths[++j] != NULL)
	{
		path = check_cmd(paths[j], cmd);
		if (path != NULL)
			break ;
	}
	if (path == NULL)
		return (NULL);
	return (path);
}

char	**get_paths(t_envt *envt)
{
	t_envt	*path;
	char	**paths;

	path = name_search("PATH", envt);
	if (path == NULL || path->value == NULL)
		return (NULL);
	paths = ft_split(path->value, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

static void	get_exit_status(t_pid *node, int *exit_status)
{
	while (node != NULL)
	{
		*exit_status = 0;
		waitpid(node->pid, exit_status, 0);
		if (WIFEXITED(*exit_status))
			*exit_status = WEXITSTATUS(*exit_status);
		else if (WIFSIGNALED(*exit_status))
		{
			if (WTERMSIG(*exit_status) == SIGQUIT)
				(ft_error("^\\Quit: 3\n"), *exit_status = 131);
			else if (WTERMSIG(*exit_status) == SIGINT)
				(ft_error("^C\n"), *exit_status = 130);
		}
		node = node->next;
	}
}

int	loop_on_cmd(t_shell *main, t_toexec *node)
{
	main->paths = get_paths(main->envt);
	while (node != NULL)
	{
		redirect_cmd(main, node);
		node = node->next;
	}
	get_exit_status(main->pid, &main->exit_status);
	(clear_pid(&main->pid), main->pid = NULL);
	if (main->paths != NULL)
		ft_free(main->paths);
	restore_std(main, 2);
	return (0);
}
