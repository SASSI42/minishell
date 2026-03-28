/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:29:29 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/10 18:35:50 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_single_quot(char *line, t_shell *main)
{
	int	j;
	int	i;

	i = 0;
	j = i;
	while (line[++i] && line[i] != '\'')
		;
	if (add_node(ft_substr(line, j, (i - j + 1)), &main->words, main))
		return (NULL);
	i++;
	return (line + i);
}

static char	*add_word(char *line, t_shell *main)
{
	int	j;
	int	i;

	i = 0;
	j = i;
	if (line[i] == '$')
		i++;
	while (line[i] && (!meta_char_2(line[i])))
		i++;
	if (add_node(ft_substr(line, j, (i - j)), &main->words, main))
		return (NULL);
	return (line + i);
}

static char	*add_char(char *line, t_shell *main, int i, int j)
{
	if (add_node(ft_substr(line, 0, i), &main->words, main))
		return (NULL);
	if (*line == '<' && i != 1)
	{
		i--;
		while (line[++i] && line[i] == ' ')
			if (add_node(ft_substr(line + 2, 0, 1), &main->words, main))
				return (NULL);
		j = i;
		while (line[i])
		{
			if (line[i] == '"')
				while (line[++i] != '"')
					;
			else if (line[i] == '\'')
				while (line[++i] != '\'')
					;
			if (meta_char_3(line[++i]))
				break ;
		}
		if (add_node(ft_substr(line, j, i - j), &main->words, main))
			return (NULL);
	}
	return (line + i);
}

static char	*add_double_quot(char *line, t_shell *main)
{
	int	i;

	i = 0;
	if (add_node(ft_substr(line, 0, 1), &main->words, main))
		return (NULL);
	line++;
	while (*line && *line != '"')
	{
		if (*line == '$' && *(line + 1) == '?')
			line = add_char(line, main, 2, 0);
		else if (line[i] != '"' && meta_char_1(*(line)))
			line = add_char(line, main, 1, 0);
		else if (!meta_char_1(*(line)))
			line = add_word(line, main);
	}
	if (add_node(ft_substr(line, i, 1), &main->words, main))
		return (NULL);
	i++;
	return (line + i);
}

int	word_node(t_shell *main)
{
	char	*line;

	line = main->line;
	while (*line)
	{
		if (*line == '"')
			line = add_double_quot(line, main);
		else if (*line == '\'')
			line = add_single_quot(line, main);
		else if ((*line == '$' && *(line + 1) == '?')
			|| ((*line == '>' && *(line + 1) == '>')
				|| (*line == '<' && *(line + 1) == '<')))
			line = add_char(line, main, 2, 0);
		else if (meta_char_1(*line)
			&& !((*line == '>' && *(line + 1) == '>')
				|| (*line == '<' && *(line + 1) == '<')))
			line = add_char(line, main, 1, 0);
		else if (!meta_char_1(*line))
			line = add_word(line, main);
		if (!line)
			return (free(main->line), 1);
	}
	return (0);
}
