/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:02:09 by msassi            #+#    #+#             */
/*   Updated: 2024/06/14 10:58:49 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	trim_beg(char const *s1, char const *set)
{
	size_t	f;
	size_t	x;

	f = 0;
	while (s1[f] != '\0')
	{
		x = 0;
		while (set[x] != '\0')
		{
			if (s1[f] == set[x])
			{
				f++;
				break ;
			}
			x++;
		}
		if (set[x] == '\0')
			break ;
	}
	return (f);
}

static int	trim_end(char const *s1, char const *set)
{
	size_t	x;
	size_t	a;

	a = ft_strlen(s1) - 1;
	while (a > 0)
	{
		x = 0;
		while (set[x] != '\0')
		{
			if (s1[a] == set[x])
			{
				a--;
				break ;
			}
			x++;
		}
		if (set[x] == '\0')
			break ;
	}
	return (a);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*a;
	int		s;
	int		e;
	int		i;

	i = 0;
	if (s1 == 0)
		return (0);
	if (set == 0)
		return (ft_strdup(s1));
	s = trim_beg(s1, set);
	if (s == ft_strlen(s1))
		return (ft_strdup(""));
	e = trim_end(s1, set);
	a = (char *)malloc(e - s + 2);
	if (a == 0)
		return (0);
	while (s <= e)
	{
		a[i] = s1[s];
		i++;
		s++;
	}
	a[i] = '\0';
	return (a);
}
