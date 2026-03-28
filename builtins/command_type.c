/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:48:59 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 18:37:54 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_type(char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (2);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (3);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (4);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (5);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (6);
	else
		return (7);
}

int	execute_builtins(t_shell *main, t_toexec *node, int type)
{
	if (type == 0 || type == 10)
		return (ft_cd(node->cmd, main->envt));
	else if (type == 1 || type == 11)
		return (ft_echo(node->cmd));
	else if (type == 2 || type == 12)
		return (ft_env(main->envt, node->cmd));
	else if (type == 3 || type == 13)
		return (ft_exit(main, node->cmd, main->exit_status, type));
	else if (type == 4 || type == 14)
		return (ft_export(node->cmd, &main->envt));
	else if (type == 5 || type == 15)
		return (ft_pwd());
	else if (type == 6 || type == 16)
		return (ft_unset(node->cmd, &main->envt));
	return (0);
}
