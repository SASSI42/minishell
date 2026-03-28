/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_quot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:18:54 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 18:53:42 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	double_quot(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '"')
		{
			while (line[++i] && line[i] != '"')
				;
			if (line[i] && line[i] == '"')
				return (0);
			if (i == ft_strlen(line))
				return (1);
		}
	}
	return (0);
}

static int	single_quot(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			while (line[++i] && line[i] != '\'')
				;
			if (line[i] && line[i] == '\'')
				return (0);
			if (i == ft_strlen(line))
				return (1);
		}
	}
	return (0);
}

int	check_quot(char *line)
{
	if (*line == '"')
	{
		if (double_quot(line))
			return (1);
	}
	else if (*line == '\'')
	{
		if (single_quot(line))
			return (1);
	}
	return (0);
}

static int	ft_check_pipe(char c)
{
	if (c == '>' || c == '<')
		return (0);
	if (c == '|')
		return (1);
	return (2);
}

int	check_pipe(char *line, int i)
{
	int	y;

	y = -1;
	if (!i || line[i + 1] == '|' || !line[i + 1])
		return (1);
	if (line[i - 1] == '>')
		return (0);
	while (++y <= i && meta_char_3(line[y]))
		if (line[y] == '|')
			return (1);
	y = i;
	while (--y >= 0 && (line[y] == ' ' || line[y] == '>'
			|| line[y] == '<' || line[y] == '\t'))
		if (line[y] == '<' || line[y] == '>')
			return (1);
	if (line[i + 1] != '|')
	{
		while (line[++i] && meta_char_3(line[i]))
		{
			if (ft_check_pipe(line[i]) != 2)
				return (ft_check_pipe(line[i]));
		}
		return (1 * !line[i]);
	}
	return (0);
}
