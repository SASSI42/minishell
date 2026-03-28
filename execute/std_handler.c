/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:54:21 by msassi            #+#    #+#             */
/*   Updated: 2024/06/12 21:56:41 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dup_in(int *fd)
{
	if (dup2(fd[0], 0) == -1)
		return (close(fd[0]), func_error("dup2"), -1);
	close(fd[0]);
	return (0);
}

int	dup_std(t_shell *node)
{
	node->std_in = dup(0);
	if (node->std_in == -1)
		return (func_error("dup"), -1);
	node->std_out = dup(1);
	if (node->std_out == -1)
		return (func_error("dup"), -1);
	return (0);
}

int	restore_std(t_shell *main, int i)
{
	if (i != 0)
	{
		if (dup2(main->std_out, 1) == -1)
			return (func_error("dup2"), -1);
	}
	if (i != 1)
	{
		if (dup2(main->std_in, 0) == -1)
			return (func_error("dup2"), -1);
	}
	if (i == -1)
	{
		close(main->std_in);
		close(main->std_out);
		main->std_in = -1;
		main->std_out = -1;
	}
	return (0);
}

void	ft_close(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
