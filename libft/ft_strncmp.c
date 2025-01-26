/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:27:01 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 07:19:19 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t l)
{
	size_t	i;

	i = 0;
	if (l == 0)
		return (0);
	while (((unsigned char)s1[i] == (unsigned char)s2[i])
		&& ((unsigned char)s1[i] != '\0' && (unsigned char)s2[i] != '\0')
		&& i < l)
		i++;
	if (i == l)
		i--;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
