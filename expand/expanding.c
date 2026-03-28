/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:45:50 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/26 20:05:44 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_s_export(t_words *words, t_shell *main)
{
	if (words->type == PIPE)
		main->s_export = 0;
	else if (ft_strlen(words->word) == ft_strlen("export")
		&& !ft_strncmp(words->word, "export", ft_strlen("export"))
		&& if_all_space(&words) != -1)
		main->s_export = 1;
	else if (words->type == WHITESPACE
		&& words->class == GENERAL && main->s_export == 2)
		main->s_export = 1;
}

static int	ft_expand_0(t_words **words, t_shell *main)
{
	if (main->s_export == 1 && (*words)->word[0] == '=')
		main->s_export_1 = 3;
	main->s_export = 2;
	if ((*words)->type == ENV)
	{
		if (expand_0(words, main) == -1)
			return (-1);
	}
	return (0);
}

static int	ft_expand_1(t_words **words, t_shell *main)
{
	if ((*words)->type == WHITESPACE && (*words)->class == GENERAL
		&& main->s_export_1 == 3)
		main->s_export_1 = 0;
	else if ((*words)->type == ENV || (*words)->type == EXPORT
		|| (*words)->type == D_QUOTE || (*words)->type == S_QUOTE)
	{
		if (main->s_export == 1 && ((*words)->type == ENV
				|| (*words)->type == D_QUOTE || (*words)->type == S_QUOTE))
			main->s_export_1 = 3;
		if (main->s_export_1 == 3 && (*words)->type == EXPORT)
			(*words)->type = ENV;
		if ((*words)->type != D_QUOTE && (*words)->type != S_QUOTE)
			if (expand_1(words, main) == -1)
				return (-1);
	}
	return (0);
}

static int	if_cnd1(t_words *words, t_shell *main)
{
	if ((words->type == WHITESPACE && main->s_export_1 == 3)
		|| (words->type == ENV || words->type == EXPORT
			|| words->type == D_QUOTE || words->type == S_QUOTE))
		return (1);
	return (0);
}

int	ft_expand(t_shell *main, t_words **words)
{
	t_words	*tmp;

	tmp = *words;
	main->s_export = 0;
	while (tmp)
	{
		ft_s_export(tmp, main);
		if (main->s_export == 1 && !ft_strchr(tmp->word, '='))
		{
			if (ft_expand_0(&tmp, main) == -1)
				return (-1);
		}
		else if (if_cnd1(tmp, main))
		{
			if (ft_expand_1(&tmp, main) == -1)
				return (-1);
		}
		else if (tmp->type == E_STATUS)
		{
			if (ft_expand_2(tmp, main) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
