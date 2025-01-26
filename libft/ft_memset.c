/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:54:52 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:33:37 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	_c;

	i = 0;
	a = (unsigned char *)b;
	_c = (unsigned char)c;
	while (len > i)
	{
		a[i] = _c;
		i++;
	}
	return (a);
}
