/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:22:45 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:40:47 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t l)
{
	size_t	i;
	size_t	len_src;
	size_t	len_dst;
	size_t	k;

	len_src = ft_strlen((char *)src);
	if (l == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (l > len_dst)
		k = len_dst + len_src;
	else
		return (len_src + l);
	i = 0;
	while (src[i] != '\0' && len_dst < l - 1)
	{
		dst[len_dst] = src[i];
		i++;
		len_dst++;
	}
	dst[len_dst] = '\0';
	return (k);
}
