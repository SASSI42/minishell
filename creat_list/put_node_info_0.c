/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_node_info_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:30:42 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/30 21:43:43 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_index(t_words **words)
{
	t_words	*tmp;
	size_t	index;

	tmp = *words;
	index = 0;
	while (tmp)
	{
		if (tmp->prev && tmp->prev->type == PIPE)
			index = 0;
		tmp->index = index;
		tmp = tmp->next;
		index++;
	}
}

static void	ft_type_heredoc(t_words *words)
{
	char	*tmp_char;
	int		expnd;
	int		i;

	i = 0;
	expnd = 0;
	tmp_char = words->word;
	while (tmp_char[i])
	{
		if (tmp_char[i] == '\'' || tmp_char[i] == '"')
			expnd = 1;
		i++;
	}
	if (expnd)
		words->type = HEREDOC_O;
	else
		words->type = HEREDOC_E;
}

void	put_type(t_words **words)
{
	t_words	*tmp;

	tmp = *words;
	while (tmp)
	{
		ft_type(tmp);
		if (tmp->type == HEREDOC)
		{
			tmp = tmp->next;
			while (tmp->word[0] == ' ')
			{
				ft_type(tmp);
				tmp = tmp->next;
			}
			ft_type_heredoc(tmp);
		}
		tmp = tmp->next;
	}
}
