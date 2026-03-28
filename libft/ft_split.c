/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:05:33 by msassi            #+#    #+#             */
/*   Updated: 2024/06/14 10:58:44 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(const char *s, char c)
{
	int	x;

	x = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0' && *s != c)
			x++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (x);
}

static void	ft_stuff(const char *s, char **f, char c)
{
	int	i;
	int	e;
	int	a;

	i = 0;
	e = 0;
	while (i < count_words(s, c))
	{
		a = 0;
		while (s[e] == c)
			e++;
		while (s[e] != '\0' && s[e] != c)
		{
			f[i][a] = s[e];
			a++;
			e++;
		}
		f[i][a] = '\0';
		i++;
	}
	f[i] = 0;
}

void	ft_free(char **f)
{
	int	i;

	i = 0;
	if (f == NULL)
		return ;
	while (f[i] != NULL)
		i++;
	while (i > 0)
		free(f[--i]);
	free(f);
}

static char	**ft_allocate(const char *s, char c)
{
	char	**f;
	int		i;
	int		a;
	int		z;

	f = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (f == 0)
		return (func_error("Memmory allocation"), NULL);
	i = -1;
	z = 0;
	while (++i < count_words(s, c))
	{
		a = 0;
		while (s[z] == c)
			z++;
		while (s[z] != '\0' && s[z++] != c)
			a++;
		f[i] = (char *)malloc(a + 1);
		if (f[i] == 0)
		{
			ft_free(f);
			return (func_error("Memmory allocation"), NULL);
		}
	}
	return (f);
}

char	**ft_split(const char *s, char c)
{
	char	**f;

	if (s == 0)
		return (0);
	f = ft_allocate(s, c);
	if (f == 0)
		return (0);
	ft_stuff(s, f, c);
	return (f);
}
