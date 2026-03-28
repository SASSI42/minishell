/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_new_info_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:36:59 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/28 13:15:07 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	type_word_1(t_words **words)
{
	t_words	*tmp;

	tmp = *words;
	while (tmp && tmp->prev && tmp->prev->type == WHITESPACE)
		tmp = tmp->prev;
	tmp = tmp->prev;
	if (tmp && tmp->type == OUT_RED)
		(*words)->type = FILE_OUT;
	else if (tmp && tmp->type == IN_RED)
		(*words)->type = FILE_IN;
	else if (tmp && tmp->type == APPEND)
		(*words)->type = APPEND_F;
	else
		(*words)->type = WORD;
}

static void	type_word(t_words *words)
{
	if (words->prev && (words->prev->type == FILE_OUT && words->rd == NO))
	{
		words->type = FILE_OUT;
		return ;
	}
	else if (words->prev && (words->prev->type == FILE_IN && words->rd == NO))
	{
		words->type = FILE_IN;
		return ;
	}
	else if (words->prev && (words->prev->type == APPEND_F && words->rd == NO))
	{
		words->type = APPEND_F;
		return ;
	}
	type_word_1(&words);
}

void	ft_new_type_0(t_words *words, int i)
{
	if (i == 1)
	{
		words->type = IN_RED;
		words->main->s_rd = 1;
	}
	if (i == 2)
	{
		words->type = APPEND;
		words->main->s_rd = 1;
	}
	if (i == 3)
	{
		words->type = OUT_RED;
		words->main->s_rd = 1;
	}
	if (i == 4)
	{
		type_word(words);
		words->main->s_rd = 0;
	}
}

void	type_space(t_words **words)
{
	t_words	*tmp;

	tmp = NULL;
	if ((*words)->prev && (*words)->prev->type == FILE_IN)
		(*words)->type = FILE_IN;
	else if ((*words)->prev && (*words)->prev->type == FILE_OUT)
		(*words)->type = FILE_OUT;
	else if ((*words)->prev && (*words)->prev->type == APPEND_F)
		(*words)->type = APPEND_F;
	else if ((*words)->prev)
	{
		tmp = (*words)->prev;
		while (tmp && tmp->type == WHITESPACE)
			tmp = tmp->prev;
		if (tmp && tmp->type == IN_RED)
			(*words)->type = FILE_IN;
		else if (tmp && tmp->type == OUT_RED)
			(*words)->type = FILE_OUT;
		else if (tmp && tmp->type == APPEND)
			(*words)->type = APPEND_F;
	}
}
