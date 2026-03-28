/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:42:19 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/12 19:10:55 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sigv;

int	if_heredoc_del(char *str, char *word)
{
	if (ft_strlen(str) == ft_strlen(word)
		&& !ft_strncmp(str, word, ft_strlen(str)))
		return (1);
	return (0);
}

static int	here_line(t_words *words, t_shell *main)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (if_heredoc_del(str, words->word))
		{
			free(str);
			break ;
		}
		free(str);
	}
	if (g_sigv == 1)
	{
		words->main->exit_status = 1;
		g_sigv = 0;
		return (restore_std(main, 0), -1);
	}
	return (restore_std(main, 0), 0);
}

void	open_here(t_words **words, t_shell *main)
{
	t_words	*tmp;

	tmp = *words;
	while (tmp)
	{
		if (tmp->type == HEREDOC_E || tmp->type == HEREDOC_O)
			if (here_line(tmp, main) == -1)
				return ;
		tmp = tmp->next;
	}
}
