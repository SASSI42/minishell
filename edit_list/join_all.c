/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:58:30 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/31 12:33:04 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	if_cnd_1(t_words *tmp_0)
{
	if ((tmp_0->type != WORD && tmp_0->type != S_QUOTE
			&& tmp_0->type != D_QUOTE)
		|| (tmp_0->next->type != WORD && tmp_0->next->type != S_QUOTE
			&& tmp_0->next->type != D_QUOTE))
		return (1);
	else if (tmp_0->next && ((tmp_0->type == WORD
				&& (tmp_0->next->type == D_QUOTE
					|| tmp_0->next->type == S_QUOTE))
			|| ((tmp_0->type == D_QUOTE || tmp_0->type == S_QUOTE)
				&& tmp_0->next->type == WORD)
			|| (tmp_0->type == WORD && tmp_0->next->type == WORD)
			|| ((tmp_0->type == S_QUOTE || tmp_0->type == D_QUOTE)
				&& (tmp_0->type == S_QUOTE || tmp_0->type == D_QUOTE))))
		return (2);
	return (0);
}

static int	word0_word1(t_words *tmp_0)
{
	char	*word_0;
	char	*word_1;

	word_0 = tmp_0->word;
	word_1 = tmp_0->next->word;
	tmp_0->word = ft_strjoin(word_0, word_1);
	if (!tmp_0->word)
		return (-1);
	free(word_0);
	return (0);
}

static int	join_words_0(t_words *tmp_0)
{
	t_words	*tmp_1;
	t_words	*tmp_2;

	if (word0_word1(tmp_0) == -1)
		return (-1);
	free(tmp_0->next->word);
	tmp_1 = tmp_0;
	tmp_0 = tmp_0->next->next;
	if (tmp_0)
	{
		tmp_2 = tmp_0;
		tmp_1->next = tmp_2;
		free(tmp_0->prev);
		tmp_2->prev = tmp_1;
	}
	else
	{
		free(tmp_1->next);
		tmp_1->next = NULL;
	}
	return (tmp_0 = tmp_1, 0);
}

int	join_quote_words(t_words **words)
{
	t_words	*tmp;

	tmp = *words;
	while (tmp && tmp->next)
	{
		if (tmp->type == E_STATUS)
			tmp->type = WORD;
		if (tmp->next->type == E_STATUS)
			tmp->next->type = WORD;
		if (if_cnd_1(tmp) == 1)
			tmp = tmp->next;
		else if (if_cnd_1(tmp) == 2)
		{
			if (tmp->next->rd == YES || tmp->rd == YES)
				tmp->rd = YES;
			if (tmp->next->class == DOUBLE_QUOTE || tmp->class == DOUBLE_QUOTE)
				tmp->class = DOUBLE_QUOTE;
			if (tmp->next->class == SINGLE_QUOTE || tmp->class == SINGLE_QUOTE)
				tmp->class = SINGLE_QUOTE;
			if (join_words_0(tmp) == -1)
				return (-1);
			tmp->type = WORD;
		}
	}
	return (0);
}

int	join_double_quote(t_words **words)
{
	t_words	*tmp_0;

	tmp_0 = *words;
	while (tmp_0 && tmp_0->next)
	{
		if ((tmp_0->class == DOUBLE_QUOTE && tmp_0->next->class == DOUBLE_QUOTE)
			|| (tmp_0->class == SINGLE_QUOTE
				&& tmp_0->next->class == SINGLE_QUOTE))
		{
			if (join_words_0(tmp_0) == -1)
				return (-1);
		}
		else
			tmp_0 = tmp_0->next;
	}
	return (0);
}
