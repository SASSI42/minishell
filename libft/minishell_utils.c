/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:31:13 by msassi            #+#    #+#             */
/*   Updated: 2024/06/14 10:58:33 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_sign(const char *str, int *s, int *i)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if ((str[*i]) == '-' )
			*s = (*s) * (-1);
		(*i)++;
	}
}

int	ft_atoi(const char *str, long *nbr)
{
	int		i;
	int		s;
	size_t	f;
	size_t	min;

	i = 0;
	s = 1;
	f = 0;
	min = 9223372036854775807;
	min++;
	skip_sign(str, &s, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		f = f * 10 + (str[i] - '0');
		i++;
		if (f > 9223372036854775807 && s == 1)
			return (-1);
		if (f > min && (s == -1))
			return (-1);
	}
	if (i == 0 || str[i] != '\0')
		return (-1);
	*nbr = (ssize_t)f * s;
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if (((c >= 'a') && (c <= 'z'))
		|| ((c >= 'A') && (c <= 'Z')))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
