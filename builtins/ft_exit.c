/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:40:02 by msassi            #+#    #+#             */
/*   Updated: 2024/06/13 23:37:45 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_exit(int type)
{
	if (type == 3)
		ft_error("exit\n");
}

int	ft_exit(t_shell *main, char **cmd, int exit_stat, int type)
{
	char			*trimed;
	unsigned char	ret;
	long			nbr;
	int				i;

	i = 0;
	nbr = 0;
	while (cmd[i] != NULL)
		i++;
	if (i == 1)
		(free_main(main), print_exit(type), exit(exit_stat));
	trimed = ft_strtrim(cmd[1], " \t");
	if (ft_atoi(trimed, &nbr) == -1)
		return (print_exit(type), ft_error("minishell: exit: "),
			ft_error(cmd[1]), ft_error(": numeric argument required\n"),
			free(trimed), free_main(main), exit(255), 1);
	free(trimed);
	if (i > 2)
		return (print_exit(type),
			ft_error("minishell: exit: too many arguments\n"), 1);
	ret = nbr;
	return (print_exit(type), free_main(main), exit(ret), 0);
}
