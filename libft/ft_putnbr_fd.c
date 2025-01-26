/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:22:18 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:33:18 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	l;

	l = n;
	if (l < 0)
	{
		write(fd, "-", 1);
		l *= -1;
	}
	if (l > 9)
	{
		ft_putnbr_fd(l / 10, fd);
	}
	ft_putchar_fd(l % 10 + '0', fd);
}
