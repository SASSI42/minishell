/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:38:42 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 14:31:33 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_pwd(t_envt *envt, char *pwd, char *old_pwd)
{
	t_envt	*var;

	var = name_search("PWD", envt);
	if (var != NULL)
	{
		free(var->value);
		var->value = pwd;
	}
	else
		free(pwd);
	var = name_search("OLDPWD", envt);
	if (var != NULL)
	{
		free(var->value);
		var->value = old_pwd;
	}
	else
		free(old_pwd);
}

static void	cd_error(void)
{
	ft_error("cd: error retrieving current directory: getcwd: ");
	ft_error("cannot access parent directories: No such file or directory\n");
}

int	ft_cd(char **cmd, t_envt *envt)
{
	t_envt	*home;
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	if (cmd[1] == NULL)
	{
		home = name_search("HOME", envt);
		if (home == NULL)
			return (free(old_pwd),
				ft_error("minishell: cd: HOME not set\n"), 1);
		if (chdir(home->value) != 0)
			return (perror(home->value), free(old_pwd), 1);
	}
	else
	{
		if (chdir(cmd[1]) != 0)
			return (free(old_pwd), ft_error("misishell: cd: "),
				perror(cmd[1]), 1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		cd_error();
	set_pwd(envt, pwd, old_pwd);
	return (0);
}
