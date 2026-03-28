/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:55:16 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/10 17:18:54 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	if_cnd1(t_words *words)
{
	if ((words->type == WORD && words->rd != NO)
		|| (words->type == WORD && words->rd == NO))
		return (1);
	return (0);
}

static int	put_args(t_toexec *toexec, t_words **words, size_t j)
{
	size_t		i;
	t_words		*tmp;

	tmp = *words;
	i = 0;
	toexec->cmd = (char **)malloc(sizeof(char *) * (j + 1));
	if (!toexec->cmd)
		return (ft_putstr_fd("minishell: error malloc", 2)
			, (*words)->main->exit_status = 1, -1);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->word && if_cnd1(tmp))
		{
			toexec->cmd[i] = ft_strdup(tmp->word);
			if (!toexec->cmd[i])
				return (free_str(i, toexec->cmd), -1);
			i++;
		}
		tmp = tmp->next;
	}
	return (toexec->cmd[i] = NULL, 0);
}

int	put_cmd_toexec(t_words **words, t_toexec **toexec)
{
	t_toexec	*tmp_exec_0;
	t_words		*tmp_0;
	t_words		*tmp_1;
	int			j;

	tmp_exec_0 = *toexec;
	tmp_0 = *words;
	while (tmp_exec_0)
	{
		j = 0;
		if (tmp_0 && tmp_0->type == PIPE)
			tmp_0 = tmp_0->next;
		tmp_1 = tmp_0;
		while (tmp_0 && tmp_0->type != PIPE)
		{
			if (if_cnd1(tmp_0))
				j++;
			tmp_0 = tmp_0->next;
		}
		if (put_args(tmp_exec_0, &tmp_1, j) == -1)
			return (-1);
		tmp_exec_0 = tmp_exec_0->next;
	}
	return (0);
}
