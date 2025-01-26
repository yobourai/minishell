/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:23:48 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:25:33 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*_s;
	char	*_d;

	i = 0;
	_s = (char *)src;
	_d = (char *)dst;
	if (_s == NULL && _d == NULL)
		return (NULL);
	while (n > 0)
	{
		_d[i] = _s[i];
		i++;
		n--;
	}
	return (dst);
}
