/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:55:44 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 18:57:47 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_quot(t_shell *main, int i, char q)
{
	if (check_quot(main->line + i) && q == 's')
	{
		ft_putendl_fd("minishell: syntax error single quote", 2);
		return (main->s_error = -1, -1);
	}
	if (check_quot(main->line + i) && q == 'd')
	{
		ft_putendl_fd("minishell: syntax error double quote", 2);
		return (main->s_error = -1, -1);
	}
	return (0);
}

static int	ft_pipe_rd(t_shell *main, int i)
{
	if (main->line[i] == '|')
	{
		if (check_pipe(main->line, i))
			return (ft_putendl_fd("minishell: syntax error near \
unexpected token `|'", 2), main->s_error = -1, -1);
	}
	if (main->line[i] == '<')
	{
		if (check_rd1(main->line, i) == 1)
			return (ft_putendl_fd("minishell: syntax error near \
unexpected token `<'", 2), main->s_error = -1, -1);
		if (check_rd1(main->line, i) == 2)
			return (ft_putendl_fd("minishell: syntax error near \
unexpected token `newline'", 2), main->s_error = -1, -1);
	}
	if (main->line[i] == '>')
	{
		if (check_rd2(main->line, i) == 1)
			return (ft_putendl_fd("minishell: syntax error near \
unexpected token `>'", 2), main->s_error = -1, -1);
		if (check_rd2(main->line, i) == 2)
			return (ft_putendl_fd("minishell: syntax error near \
unexpected token `newline'", 2), main->s_error = -1, -1);
	}
	return (0);
}

static char	*syntax_error(t_shell *main)
{
	ssize_t	i;

	i = -1;
	while (main->line[++i])
	{
		if (main->line[i] == '\'')
		{
			if (ft_quot(main, i, 's') == -1)
				break ;
			while (main->line[++i] && main->line[i] != '\'')
				;
		}
		if (main->line[i] == '"')
		{
			if (ft_quot(main, i, 'd') == -1)
				break ;
			while (main->line[++i] && main->line[i] != '"')
				;
		}
		if (ft_pipe_rd(main, i) == -1)
			break ;
	}
	return (main->line[i] = '\0', main->line);
}

static int	here_syntax(t_shell *main)
{
	int	i;

	i = 0;
	if (main->s_error == -1)
	{
		main->exit_status = 258;
		while (main->line[i] && main->line[i + 1] && main->line[i + 2])
		{
			if (main->line[i] == '<' && main->line[i + 1] == '<')
			{
				i += 2;
				while (main->line[i] == ' ' || main->line[i] == '\t')
					i++;
				if (main->line[i])
					return (-1);
			}
			i++;
		}
		return (-2);
	}
	return (0);
}

int	ft_pars(t_shell *main)
{
	syntax_error(main);
	main->s_error = here_syntax(main);
	if (!main->s_error && main->line[0])
	{
		if (creat_list(main) == -1)
			return (free(main->line), -1);
		if (creat_toexec(main) == -1)
			return (free(main->line), free_all_words(&main->words), -1);
		free_all_words(&main->words);
	}
	else if (main->s_error == -1 && main->line[0])
	{
		if (creat_list(main) == -1)
			return (free(main->line), -1);
		open_here(&main->words, main);
		return (free(main->line), free_all_words(&main->words), -2);
	}
	free(main->line);
	return (0);
}
