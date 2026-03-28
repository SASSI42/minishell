/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:10:46 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 18:57:19 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_rd1(char *line, int i)
{
	while (line[i] && line[++i])
	{
		if (line[i] && (line[i] == '<' || line[i] == '>'))
			i++;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] && (line[i] == '|' || line[i] == '<'))
			return (1);
		if (line[i])
			return (0);
	}
	return (2);
}

static int	if_cnd1(char *line, int i)
{
	if (i == ft_strlen(line) - 1
		&& (i == 0 || (line[i - 1] != '>' && line[i - 1] != '|')))
		return (1);
	return (0);
}

int	check_rd1(char *line, int i)
{
	int	y;

	if (line[i + 1] == '<' && !line[i + 2])
		return (2);
	if (if_cnd1(line, i))
	{
		while (--i >= 0 && (line[i] == ' ' || line[i] == '\t'))
			;
		if (i >= 0 && (line[i] == '>' || line[i] == '<'))
			return (1);
		return (2);
	}
	y = i;
	while (--y >= 0)
	{
		if (line[y] == '<')
			y--;
		while (y >= 0 && (line[y] == ' ' || line[y] == '\t'))
			y--;
		if (y >= 0 && (line[y] == '>' || line[y] == '<'))
			return (1);
		if (y >= 0 && (line[y] != '>' && line[y] != '<'))
			return (ft_check_rd1(line, i));
	}
	return (ft_check_rd1(line, i));
}

static int	ft_check_rd2(char *line, int i)
{
	while (line[i] && line[++i])
	{
		if (line[i] && line[i] == '>')
			i++;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] && (line[i] == '|' || line[i] == '<'))
			return (1);
		if (line[i])
			return (0);
	}
	return (2);
}

int	check_rd2(char *line, int i)
{
	int	y;

	if (line[i + 1] == '>' && !line[i + 2])
		return (2);
	if (i == ft_strlen(line) - 1
		|| (i == ft_strlen(line) - 1 && line[i - 1] == '<'))
		return (2);
	y = i;
	while (--y >= 0)
	{
		if (line[y] == '>' || line[y] == '<')
			y--;
		while (y > 0 && (line[y] == ' ' || line[y] == '\t'))
			y--;
		if (y >= 0 && line[y] == '|')
			return (ft_check_rd2(line, i));
	}
	return (ft_check_rd2(line, i));
}
