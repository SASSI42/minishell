/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:38:34 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 14:48:21 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *s)
{
	size_t	i;

	if (s == 0)
		return ;
	i = ft_strlen(s);
	write(2, s, i);
}

void	cmd_error(char *s)
{
	ft_error("minishell: ");
	ft_error(s);
	ft_error(": command not found\n");
}

void	func_error(char *s)
{
	ft_error("Error: ");
	ft_error(s);
	ft_error(" failed\n");
}

int	ft_env(t_envt *envt, char **cmd)
{
	if (cmd[1] != NULL)
		return (ft_error("env: "), ft_error(cmd[1])
			, ft_error(": No such file or directory\n"), 127);
	while (envt != NULL)
	{
		if (envt->value != NULL)
			printf("%s=%s\n", envt->name, envt->value);
		envt = envt->next;
	}
	return (0);
}
