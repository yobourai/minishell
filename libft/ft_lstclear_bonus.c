/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:35:32 by yobourai          #+#    #+#             */
/*   Updated: 2024/01/15 04:55:24 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*new;

	if (!*lst || !del)
		return ;
	new = *lst;
	while (new)
	{
		del(new->content);
		node = new->next;
		free(new);
		new = node;
	}
	*lst = NULL;
}
