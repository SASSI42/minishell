/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:55:23 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 18:41:59 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	pars_env(t_shell *main, t_words **tmp)
{
	if ((*tmp)->prev == NULL)
		add_to_top(main, tmp);
	else
		add_sub_list(main, tmp);
	return (0);
}

static int	exp_env(t_shell *main, t_words **words)
{
	t_words	*tmp;

	tmp = NULL;
	if ((*words)->type != ENV)
	{
		(*words)->type = WORD;
		(*words)->rd = YES;
	}
	else if ((*words)->type == ENV)
	{
		if ((*words)->word)
		{
			tmp = *words;
			if (pars_env(main, words) == -1)
				return (-1);
			(free(tmp->word), free(tmp));
		}
		else
		{
			(*words)->rd = NO;
			(*words)->class = ENVT;
			(*words)->type = WORD;
		}
	}
	return (0);
}

static int	replace_env(t_words *words, t_shell *main, char *name_value)
{
	t_envt	*tmp;

	tmp = main->envt;
	while (tmp)
	{
		if (ft_strlen(name_value) == ft_strlen(tmp->name)
			&& !ft_strncmp(name_value, tmp->name, ft_strlen(tmp->name)))
		{
			free(words->word);
			words->word = ft_strdup(tmp->value);
			if (!words->word)
				return (-1);
			return (0);
		}
		tmp = tmp->next;
	}
	if (words->word[1] != '\0')
	{
		free(words->word);
		words->word = NULL;
	}
	return (0);
}

int	expand_1(t_words **words, t_shell *main)
{
	if (replace_env(*words, main, (*words)->word + 1) == -1)
		return (-1);
	if (exp_env(main, words) == -1)
		return (-1);
	return (0);
}

int	expand_0(t_words **words, t_shell *main)
{
	int		i;
	char	*name_value;
	char	*tmp_char_0;
	char	*tmp_char_1;

	i = 0;
	while ((*words)->word && (*words)->word[i] != '=')
		i++;
	name_value = ft_substr((*words)->word, 1, i - 1);
	if (!name_value)
		return (-1);
	tmp_char_0 = ft_substr((*words)->word, i, ft_strlen((*words)->word) - 1);
	if (!tmp_char_0)
		return (free(name_value), -1);
	if (replace_env((*words), main, name_value) == -1)
		return (-1);
	tmp_char_1 = (*words)->word;
	(*words)->word = ft_strjoin(tmp_char_1, tmp_char_0);
	if (!(*words)->word)
		return (free(name_value), free(tmp_char_0), -1);
	(free(name_value), free(tmp_char_0), free(tmp_char_1));
	if (exp_env(main, words) == -1)
		return (-1);
	return (0);
}
