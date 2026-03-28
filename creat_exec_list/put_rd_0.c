/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_rd_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:50:53 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/10 17:19:19 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	if_cnd2(t_words *words)
{
	if (words->rd == NO && !words->word)
		return (0);
	if (words->rd == NO && words->word[0] == ' ')
		return (0);
	return (1);
}

static int	if_cnd3(t_words *words)
{
	if (words && (words->type == FILE_IN || words->type == FILE_OUT
			|| words->type == APPEND_F || words->type == HEREDOC_O
			|| words->type == HEREDOC_E) && if_cnd2(words))
		return (1);
	return (0);
}

int	put_file_rd(t_rds *rds, t_words **words, size_t j)
{
	size_t		i;
	t_words		*tmp;

	tmp = *words;
	rds->rd = (char **)malloc(sizeof(char *) * (j + 1));
	if (!rds->rd)
		return (ft_putstr_fd("minishell: error malloc", 2)
			, (*words)->main->exit_status = 1, -1);
	i = 0;
	rds->rd[i] = ft_strdup(tmp->word);
	if (!rds->rd[i])
		return (-1);
	tmp = tmp->next;
	while (tmp && tmp->type != APPEND && tmp->type != IN_RED
		&& tmp->type != OUT_RED && tmp->type != HEREDOC && tmp->type != PIPE)
	{
		if (if_cnd3(tmp))
		{
			rds->rd[++i] = ft_strdup(tmp->word);
			if (!rds->rd[i])
				return (free_str(i, rds->rd), -1);
		}
		tmp = tmp->next;
	}
	return (rds->rd[++i] = NULL, 0);
}
