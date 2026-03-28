/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:03:37 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 12:26:59 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	write_env_value(char *str, t_envt **envt, int fd)
{
	t_envt	*tmp_env;
	char	*tmp_char;
	int		i;

	i = 0;
	tmp_env = *envt;
	while (str[++i] && !meta_char_2(str[i]))
		;
	tmp_char = ft_substr(str, 0, i);
	if (!tmp_char)
		return (-1);
	while (tmp_env)
	{
		if (ft_strlen(tmp_char) == ft_strlen(tmp_env->name)
			&& !ft_strncmp(tmp_char, tmp_env->name, ft_strlen(tmp_env->name)))
		{
			ft_putstr_fd(tmp_env->value, fd);
			break ;
		}
		tmp_env = tmp_env->next;
	}
	return (free(tmp_char), 0);
}

static int	write_exit_status(int exit_status, int fd)
{
	char	*nbr;

	nbr = ft_itoa(exit_status);
	if (!nbr)
		return (-1);
	ft_putstr_fd(nbr, fd);
	free(nbr);
	return (0);
}

static int	write_str(char *str, t_words *words, int fd, t_shell *main)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (words->type == HEREDOC_E
			&& str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			i += 2;
			if (write_exit_status(main->exit_status, fd) == -1)
				return (-1);
		}
		else if (words->type == HEREDOC_E
			&& str[i] == '$' && str[i + 1] && !meta_char_2(str[i + 1]))
		{
			if (write_env_value(str + i + 1, &main->envt, fd) == -1)
				return (-1);
			while (str[++i] && !meta_char_2(str[i]))
				;
		}
		else
			write(fd, str + i++, 1);
	}
	return (0);
}

static int	heredoc_line(t_words *words, int fd, t_shell *main)
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
		if (write_str(str, words, fd, main) == -1)
			return (-1);
		(write(fd, "\n", 1), free(str));
	}
	return (0);
}

int	open_heredoc(t_words *words, t_toexec *toexec, t_shell *main)
{
	char	*name;
	int		tmp_fd;

	name = ft_itoa((long)&(words->main));
	if (!name)
		return (main->exit_status = 1, -1);
	tmp_fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (tmp_fd == -1)
		return (free(name), ft_putstr_fd("minishell: ", 2)
			, perror("heredoc"), -1);
	toexec->input = open(name, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (toexec->input == -1)
		return (free(name), ft_putstr_fd("minishell: ", 2)
			, perror("heredoc"), close(tmp_fd), -1);
	if (unlink(name) == -1)
		return (free(name), ft_putstr_fd("minishell: ", 2)
			, perror("heredoc"), close(tmp_fd), close(toexec->input), -1);
	if (heredoc_line(words, tmp_fd, main) == -1)
		return (free(name), close(tmp_fd), close(toexec->input), -1);
	return (free(name), close(tmp_fd), 0);
}
