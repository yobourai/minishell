/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 00:38:25 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:22:05 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*_s1;
	unsigned char	*_s2;

	_s1 = (unsigned char *)s1;
	_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (_s1[i] == _s2[i] && i < n - 1)
		i++;
	if (n == i)
		return (0);
	return (_s1[i] - _s2[i]);
}
