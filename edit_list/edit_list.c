/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:32:22 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 15:21:30 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	edit_list(t_shell *main)
{
	if (!main->words)
		return (-1);
	del_double_quot(&main->words);
	if (del_single_quotes(main->words) == -1)
		return (-1);
	if (join_double_quote(&main->words) == -1)
		return (-1);
	if (join_quote_words(&main->words) == -1)
		return (-1);
	put_new_type(&(main->words));
	if (del_quot_heredoc(&(main->words)) == -1)
		return (-1);
	return (0);
}
