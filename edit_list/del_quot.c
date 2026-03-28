/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:13:13 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 15:20:58 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_double_quot(t_words **words)
{
	t_words	*tmp;

	tmp = *words;
	while (tmp)
	{
		if (tmp->type == D_QUOTE && tmp->class == DOUBLE_QUOTE)
			tmp->word[0] = '\0';
		tmp = tmp->next;
	}
}

int	del_single_quotes(t_words *words)
{
	t_words	*tmp;
	char	*tmp_char;

	tmp = words;
	while (tmp)
	{
		if (tmp->type == S_QUOTE && tmp->class == SINGLE_QUOTE)
		{
			tmp_char = tmp->word;
			tmp->word = ft_substr(tmp_char, 1, ft_strlen(tmp_char) - 2);
			if (!tmp->word)
				return (free(tmp_char), -1);
			free(tmp_char);
		}
		tmp = tmp->next;
	}
	return (0);
}

static size_t	count_len_heredoc(char	*word)
{
	size_t	len;
	int		i;

	i = -1;
	len = 0;
	while (word[++i])
	{
		if (word[i] == '"')
			while (word[++i] != '"')
				len++;
		else if (word[i] == '\'')
			while (word[++i] != '\'')
				len++;
		else
			len++;
	}
	return (len);
}

static char	*ft_quot_heredoc(char *word)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	tmp = malloc(sizeof(char) * (count_len_heredoc(word) + 1));
	if (!tmp)
		return (ft_putstr_fd("minishell: error malloc", 2), NULL);
	while (word[++i])
	{
		if (word[i] == '"')
		{
			while (word[++i] != '"')
				tmp[j++] = word[i];
		}
		else if (word[i] == '\'')
		{
			while (word[++i] != '\'')
				tmp[j++] = word[i];
		}
		else
			tmp[j++] = word[i];
	}
	return (tmp[j] = '\0', free(word), tmp);
}

int	del_quot_heredoc(t_words **words)
{
	t_words	*tmp;

	tmp = *words;
	while (tmp)
	{
		if (tmp->type == HEREDOC_O)
		{
			tmp->word = ft_quot_heredoc(tmp->word);
			if (!tmp->word)
				return ((*words)->main->exit_status = 1, -1);
		}
		tmp = tmp->next;
	}
	return (0);
}
