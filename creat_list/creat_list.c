/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:44:21 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 16:03:33 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_words	*find_l_node(t_words *last)
{
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

int	add_node(char *one_word, t_words **words, t_shell *main)
{
	t_words	*node;
	t_words	*l_node;

	if (!words || !one_word)
		return (1);
	node = malloc(sizeof(t_words));
	if (!node)
		return (ft_putstr_fd("minishell: error malloc", 2)
			, free_all_words(words), (*words)->main->exit_status = 1, 1);
	node->next = NULL;
	node->prev = NULL;
	node->main = main;
	node->word = ft_strdup(one_word);
	if (!node->word)
		return (free_all_words(words), 1);
	if (!(*words))
		*words = node;
	else
	{
		l_node = find_l_node(*words);
		l_node->next = node;
		node->prev = l_node;
	}
	return (free(one_word), 0);
}

static int	set_node(t_words *node, t_shell *main, char *one_word)
{
	node->next = NULL;
	node->prev = NULL;
	node->main = main;
	node->class = ENVT;
	node->rd = NO;
	node->word = ft_strdup(one_word);
	if (!node->word)
		return (-1);
	if (node->word[0] == ' ')
		node->type = WHITESPACE;
	else if (node->word[0] == '\'')
		node->type = S_QUOTE;
	else if (node->word[0] == '"')
		node->type = D_QUOTE;
	else if (node->word[0] != ' ')
		node->type = WORD;
	return (0);
}

int	add_node_0(char *one_word, t_words **words, t_shell *main)
{
	t_words	*node;
	t_words	*l_node;

	if (!words || !one_word)
		return (1);
	node = malloc(sizeof(t_words));
	if (!node)
		return (ft_putstr_fd("minishell: error malloc", 2)
			, free_all_words(words), (*words)->main->exit_status = 1, 1);
	if (set_node(node, main, one_word) == -1)
		return (-1);
	if (!node->word)
		return (free_all_words(words), 1);
	if (!(*words))
		*words = node;
	else
	{
		l_node = find_l_node(*words);
		l_node->next = node;
		node->prev = l_node;
	}
	return (free(one_word), 0);
}

int	creat_list(t_shell *main)
{
	if (!main->line)
		return (0);
	if (word_node(main))
		return (-1);
	put_index(&(main->words));
	put_class(&(main->words));
	put_type(&(main->words));
	if (ft_expand(main, &(main->words)) == -1)
		return (-1);
	put_class_0(main->words);
	put_index(&(main->words));
	if (edit_list(main) == -1)
		return (-1);
	return (0);
}
