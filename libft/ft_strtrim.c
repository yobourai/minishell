/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 07:33:08 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:46:51 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_bidaya(char const *s, char const *c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0' && c[j] != '\0')
	{
		if (s[i] == c[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

int	ft_nihaya(char const *s, char const *c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		i++;
	}
	if (i > 0)
		i--;
	while (i >= 0 && c[j] != '\0')
	{
		if (s[i] == c[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*_s1;

	if (!s1 || !set)
		return (NULL);
	len = -ft_bidaya(s1, set) + ft_nihaya(s1, set) + 1;
	_s1 = ft_substr(s1, ft_bidaya(s1, set), len);
	return (_s1);
}
