/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:11:01 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 07:35:38 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (src[i] != '\0' && dstsize - 1 > i)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[len] != '\0')
	{
		len++;
	}
	return (len);
}
