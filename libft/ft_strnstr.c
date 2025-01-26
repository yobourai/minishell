/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:11:54 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:45:29 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t l)
{
	size_t	i;
	size_t	j;

	if (*s2 == '\0')
		return ((char *)s1);
	if (l < 0)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i] == s2[j] && s1[i] && i < l)
		{
			i++;
			j++;
		}
		if (s2[j] == '\0')
			return ((char *)&s1[i - j]);
		i = (i - j) + 1;
	}
	return (NULL);
}
