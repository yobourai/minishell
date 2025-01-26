/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 22:09:19 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:49:14 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*_s;
	unsigned char	*_d;

	_s = (unsigned char *)src;
	_d = (unsigned char *)dst;
	if (!_s && !_d)
		return (NULL);
	if (_d < _s)
	{
		ft_memcpy(_d, _s, len);
	}
	else
	{
		i = 0;
		while (0 < len)
		{
			len--;
			_d[len] = _s[len];
			i++;
		}
	}
	return (dst);
}
