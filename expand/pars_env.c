/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:50:34 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 18:45:00 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_quot_space(char *word, t_words **words, t_shell *main)
{
	if (add_node_0(ft_substr(word, 0, 1), words, main))
		return (NULL);
	return (word + 1);
}

static char	*add_no_space(char *word, t_words **words, t_shell *main)
{
	int	j;
	int	i;

	i = 0;
	j = i;
	while (word[i] && word[i] != ' ' && word[i] != '\''
		&& word[i] != '"' && word[i] != '\t')
		i++;
	if (add_node_0(ft_substr(word, j, (i - j)), words, main))
		return (NULL);
	return (word + i);
}

static t_words	*create_sublist(t_shell *main, t_words *words)
{
	t_words	*new_exp;
	char	*word;

	new_exp = NULL;
	if (!(words)->word)
		return (NULL);
	word = words->word;
	while (*word)
	{
		if (*word == ' ' || *word == '"' || *word == '\'' || *word == '\t')
			word = add_quot_space(word, &new_exp, main);
		else
		{
			word = add_no_space(word, &new_exp, main);
		}
		if (!word)
			return (NULL);
	}
	return (new_exp);
}

void	add_to_top(t_shell *main, t_words **tmp)
{
	t_words	*sub_list;
	t_words	*sub_tmp;

	sub_list = create_sublist(main, *tmp);
	sub_tmp = sub_list;
	while (sub_tmp->next)
		sub_tmp = sub_tmp->next;
	sub_tmp->next = (*tmp)->next;
	if ((*tmp)->next)
		(*tmp)->next->prev = sub_tmp;
	(*tmp) = sub_list;
	main->words = (*tmp);
}

void	add_sub_list(t_shell *main, t_words **tmp)
{
	t_words	*sub_list;
	t_words	*sub_tmp;

	sub_list = create_sublist(main, *tmp);
	sub_tmp = sub_list;
	while (sub_tmp->next)
		sub_tmp = sub_tmp->next;
	sub_tmp->next = (*tmp)->next;
	if ((*tmp)->next)
		(*tmp)->next->prev = sub_tmp;
	(*tmp)->prev->next = sub_list;
	sub_list->prev = (*tmp)->prev;
	*tmp = sub_list;
}
