/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:29:11 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 18:38:41 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static int	out_file_redirection(t_rds *red, int fd)
{
	if (red->rd[1] == NULL || red->rd[2] != NULL)
	{
		ft_error("minishell: ambiguous redirect\n");
		return (-1);
	}
	if (ft_strcmp(red->rd[0], ">") == 0 || ft_strcmp(red->rd[0], ">>") == 0)
	{
		if (ft_strcmp(red->rd[0], ">") == 0)
			fd = open(red->rd[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			fd = open(red->rd[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			return (ft_error("minishell: "), perror(red->rd[1]), -1);
		if (dup2(fd, 1) == -1)
			return (close(fd), func_error("dup2"), -1);
		close(fd);
	}
	return (0);
}

int	redirection_handler(t_rds *red, int in_doc, int fd)
{
	while (red != NULL)
	{
		if (out_file_redirection(red, fd) != 0)
			return (-1);
		if (ft_strcmp(red->rd[0], "<") == 0)
		{
			fd = open(red->rd[1], O_RDONLY);
			if (fd == -1)
				return (ft_error("minishell: "), perror(red->rd[1]), -1);
			if (dup2(fd, 0) == -1)
				return (close(fd), func_error("dup2"), -1);
			close(fd);
		}
		else if (ft_strcmp(red->rd[0], "<<") == 0)
		{
			if (dup2(in_doc, 0) == -1)
				return (func_error("dup2"), -1);
		}
		red = red->next;
	}
	return (0);
}

static int	cmd_type(t_shell *main, t_toexec *node)
{
	int	type;
	int	id;

	type = command_type(node->cmd);
	if (type != 7 && node->next == NULL && node->prev == NULL)
		main->exit_status = execute_builtins(main, node, type);
	else
	{
		id = fork();
		if (id == -1)
			return (func_error("fork"), main->exit_status = 1, -1);
		if (id == 0)
		{
			close(main->pipein);
			if (type == 7)
				execute_cmd(main, node, main->envt);
			else
				exit(execute_builtins(main, node, type + 10));
		}
		if (add_pid(&main->pid, new_pid(id)) == -1)
			return (main->exit_status = 1, -1);
	}
	return (0);
}

int	redirect_cmd(t_shell *main, t_toexec *node)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (func_error("pipe"), main->exit_status = 1, -1);
	main->pipein = fd[0];
	if (dup2(fd[1], 1) == -1)
		return (ft_close(fd), func_error("dup2"), main->exit_status = 1, -1);
	close(fd[1]);
	if (node->next == NULL)
	{
		if (dup2(main->std_out, 1) == -1)
			return (close(fd[0]), func_error("dup2"),
				main->exit_status = 1, -1);
	}
	if (redirection_handler(node->rds, node->input, -1) == -1)
		return (dup_in(fd), main->exit_status = 1, -1);
	if (node->cmd == NULL)
		return (dup_in(fd), main->exit_status = 0, 0);
	if (cmd_type(main, node) != 0)
		return (-1);
	if (dup_in(fd) != 0)
		return (main->exit_status = 1, -1);
	return (0);
}
