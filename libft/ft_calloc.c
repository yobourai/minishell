/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:46:16 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:20:30 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if ((int)count < 0 && (int)size < 0)
		return (NULL);
	p = malloc(size * count);
	if (!p)
		return (p);
	ft_bzero(p, count * size);
	return (p);
}
