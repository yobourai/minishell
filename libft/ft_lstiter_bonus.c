/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:41:14 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 23:06:50 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	int	i ;

	i = 0;
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		i++;
		lst = lst->next;
	}
}
