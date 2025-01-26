/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 01:25:24 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:34:33 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbw(char const *s, char c)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if ((s[i] == c && s[i - 1] != c) || (s[i + 1] == '\0' && s[i] != c))
			j++;
		i++;
	}
	return (j);
}

static int	ft_nbc(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		j++;
		i++;
	}
	return (j);
}

static	void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static	char	**ft_uncj(char **tab, char const *s, char c, int j)
{
	int	i;
	int	start;
	int	slen;

	i = 0;
	start = 0;
	while (i < j)
	{
		while (s && s[start] == c)
			start++;
		slen = 0;
		slen = ft_nbc(s + start, c);
		tab[i] = ft_substr(s, start, slen);
		if (!tab[i])
		{
			ft_free(tab);
			return (NULL);
		}
		i++;
		start = slen + start;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	char	**tab;

	j = ft_nbw(s, c);
	if (!s)
		return (NULL);
	tab = (char **)malloc((j + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab = ft_uncj(tab, s, c, j);
	return (tab);
}
