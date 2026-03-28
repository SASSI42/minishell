/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_node_info_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:31:31 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 15:31:22 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	if_cnd1(t_words *words)
{
	if (words->word && words->word[0] == '\''
		&& words->word[ft_strlen(words->word) - 1] == '\''
		&& words->type != HEREDOC_E && words->type != HEREDOC_O)
		return (1);
	return (0);
}

static int	if_cnd2(t_words *words)
{
	if (words->word && words->word[0] == '"'
		&& words->type != HEREDOC_E && words->type != HEREDOC_O)
		return (1);
	return (0);
}

void	put_class(t_words **words)
{
	t_words	*tmp;

	tmp = *words;
	while (tmp)
	{
		tmp->class = GENERAL;
		if (if_cnd1(tmp))
			tmp->class = SINGLE_QUOTE;
		else if (if_cnd2(tmp))
		{
			tmp->class = DOUBLE_QUOTE;
			tmp = tmp->next;
			while (tmp)
			{
				if (tmp->word && tmp->word[0] == '"')
					break ;
				tmp->class = DOUBLE_QUOTE;
				tmp = tmp->next;
			}
			if (tmp)
				tmp->class = DOUBLE_QUOTE;
		}
		if (tmp)
			tmp = tmp->next;
	}
}

static int	if_cnd3(t_words *words)
{
	if (words->word && words->word[0] == '"' && words->class != ENVT
		&& words->type != HEREDOC_E && words->type != HEREDOC_O)
		return (1);
	return (0);
}

void	put_class_0(t_words *words)
{
	while (words)
	{
		if (words->class != ENVT)
			words->class = GENERAL;
		if (if_cnd1(words) && words->class != ENVT)
			words->class = SINGLE_QUOTE;
		else if (if_cnd3(words))
		{
			words->class = DOUBLE_QUOTE;
			words = words->next;
			while (words)
			{
				if (words->word && words->word[0] == '"')
					break ;
				words->class = DOUBLE_QUOTE;
				words = words->next;
			}
			if (words)
				words->class = DOUBLE_QUOTE;
		}
		if (words && words->class == ENVT)
			words->class = GENERAL;
		if (words)
			words = words->next;
	}
}
