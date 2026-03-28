/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:12:26 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/28 18:17:13 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_all_space(t_words **words)
{
	t_words	*tmp;
	int		i;

	tmp = *words;
	i = tmp->index;
	while (i > 0)
	{
		tmp = tmp->prev;
		if (!(tmp->type == WHITESPACE))
			return (-1);
		i--;
	}
	return (0);
}

static void	ft_type_1(t_words *words, int i)
{
	if (i)
	{
		words->type = ENV;
		if (words->main->s_export == 2)
			words->type = EXPORT;
	}
	else
	{
		words->type = WORD;
		if (ft_strlen(words->word) == ft_strlen("export")
			&& !ft_strncmp(words->word, "export", ft_strlen("export"))
			&& if_all_space(&words) != -1)
			words->main->s_export = 1;
		if (words->main->s_export == 1 && !ft_strchr(words->word, '='))
			words->main->s_export = 2;
	}
}

static void	type_space_1(t_words *words)
{
	words->type = WHITESPACE;
	if (words->class == GENERAL && words->main->s_export == 2)
		words->main->s_export = 1;
}

static void	type_pipe(t_words *words)
{
	words->type = PIPE;
	words->main->s_export = 0;
}

void	ft_type(t_words *words)
{
	words->rd = YES;
	if (white_space(words->word[0]))
		type_space_1(words);
	else if (words->word[0] == '"')
		words->type = D_QUOTE;
	else if (words->word[0] == '\'')
		words->type = S_QUOTE;
	else if (words->word[0] == '|')
		type_pipe(words);
	else if (words->word[0] == '<' && words->word[1] == '<')
		words->type = HEREDOC;
	else if (words->word[0] == '<')
		words->type = IN_RED;
	else if (words->word[0] == '>' && words->word[1] == '>')
		words->type = APPEND;
	else if (words->word[0] == '>')
		words->type = OUT_RED;
	else if (words->word[0] == '$' && words->word[1] == '?')
		words->type = E_STATUS;
	else if (words->word[0] == '$' && words->word[1])
		ft_type_1(words, 1);
	else
		ft_type_1(words, 0);
}
