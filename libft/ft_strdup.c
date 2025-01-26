/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 05:13:16 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:34:53 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s;
	char	*s2;

	s = (char *)s1;
	s2 = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s, ft_strlen(s) + 1);
	s2[ft_strlen(s)] = '\0';
	return (s2);
}
