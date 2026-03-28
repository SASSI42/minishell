/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:55:31 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 14:00:18 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_expand_2(t_words *words, t_shell *main)
{
	char	*tmp;

	tmp = words->word;
	words->word = ft_itoa(main->exit_status);
	if (!words->word)
		return (main->exit_status = 1, -1);
	free(tmp);
	return (0);
}
