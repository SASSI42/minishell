/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:26:25 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/13 14:37:57 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	j;
	size_t	lens;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (len > lens - start)
		len = lens - start;
	if (start > lens)
		len = 0;
	s1 = (char *)malloc(len + 1);
	if (!s1)
		return (ft_putstr_fd("minishell: error malloc", 2), NULL);
	j = 0;
	while (j < len)
	{
		s1[j] = s[start];
		j++;
		start++;
	}
	s1[j] = 0;
	return (s1);
}

char	*ft_strjoin1(char *s1, char *s2, char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1)
	{
		i = -1;
		while (s1[++i])
			res[i] = s1[i];
	}
	if (s2)
	{
		j = 0;
		while (s2[j])
			res[i++] = s2[j++];
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		l1;
	int		l2;
	char	*res;

	l1 = 0;
	l2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		l1 = ft_strlen(s1);
	if (s2)
		l2 = ft_strlen(s2);
	res = malloc((l1 + l2 + 1) * sizeof(char));
	if (!res)
		return (ft_putstr_fd("minishell: error malloc", 2), NULL);
	return (ft_strjoin1(s1, s2, res));
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	int		len1;

	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	s2 = (char *)malloc(len1 + 1);
	if (!s2)
		return (func_error("memory allocation"), NULL);
	i = 0;
	while (i < len1)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}
