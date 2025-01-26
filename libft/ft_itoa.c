/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 03:44:31 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:20:49 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_long(int n)
{
	long	nb;
	int		i;

	nb = n;
	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		i++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	k;

	k = n;
	len = ft_long(k);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (k < 0)
	{
		str[0] = '-';
		k *= -1;
	}
	str[len] = '\0';
	while (k > 0 && len >= 0)
	{
		len--;
		str[len] = k % 10 + '0';
		k = k / 10;
	}
	if (n == 0)
		str[0] = '0';
	return (str);
}
