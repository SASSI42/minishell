/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_new_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:21:07 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/31 20:43:35 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	if_cnd1(t_words *words)
{
	if (words->word && words->main->s_rd == 0
		&& (words->class == DOUBLE_QUOTE || words->class == SINGLE_QUOTE
			|| words->class == ENVT) && words->type != HEREDOC_E
		&& words->type != HEREDOC_O && (white_space(words->word[0])
			&& !words->word[1]))
		return (1);
	return (0);
}

static void	ft_new_type_1(t_words *words, int i)
{
	if (i == 0)
	{
		words->type = WORD;
		if (words->rd == NO)
			type_space(&words);
	}
	else if ((words->rd == NO || words->class == DOUBLE_QUOTE
			|| words->class == SINGLE_QUOTE) && i)
		type_space(&words);
}

static void	ft_new_type(t_words *words)
{
	if (words->prev && (words->prev->type == FILE_IN
			|| words->prev->type == FILE_OUT || words->prev->type == APPEND_F)
		&& (words->class == DOUBLE_QUOTE || words->class == SINGLE_QUOTE))
		words->type = words->prev->type;
	else if (if_cnd1(words))
		ft_new_type_1(words, 0);
	else if (words->word && white_space(words->word[0]) && !words->word[1])
	{
		words->type = WHITESPACE;
		ft_new_type_1(words, 1);
	}
	else if (words->class == GENERAL && words->type == PIPE)
		words->type = PIPE;
	else if (words->class == GENERAL && words->type == HEREDOC)
		words->type = HEREDOC;
	else if (words->class == GENERAL && words->type == IN_RED)
		ft_new_type_0(words, 1);
	else if (words->class == GENERAL && words->type == APPEND)
		ft_new_type_0(words, 2);
	else if (words->class == GENERAL && words->type == OUT_RED)
		ft_new_type_0(words, 3);
	else if (words->type != HEREDOC_E && words->type != HEREDOC_O)
		ft_new_type_0(words, 4);
}

void	put_new_type(t_words **words)
{
	t_words	*tmp;

	tmp = *words;
	while (tmp)
	{
		ft_new_type(tmp);
		tmp = tmp->next;
	}
}
