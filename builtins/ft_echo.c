/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:38:23 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 18:05:15 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_no_line(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '\0')
		return (0);
	while (cmd[i] != '\0')
	{
		if (i == 0 && cmd[i] != '-')
			return (0);
		if (i != 0 && cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	s;

	i = 1;
	s = 1;
	while (cmd[i] != NULL)
	{
		if (print_no_line(cmd[i]) == 0)
			break ;
		i++;
		s++;
	}
	while (cmd[i] != NULL)
	{
		if (i > s)
			write(1, " ", 1);
		write(1, cmd[i], ft_strlen(cmd[i]));
		i++;
	}
	if (s == 1)
		write(1, "\n", 1);
	return (0);
}
