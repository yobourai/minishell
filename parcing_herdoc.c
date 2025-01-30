/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_herdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:18:51 by yobourai          #+#    #+#             */
/*   Updated: 2025/01/27 14:55:47 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help_red(char ptr, int *flag)
{
	if (ptr == 30 && (*flag == 0 || *flag == 1))
	{
		if (*flag == 0)
			*flag = 1;
		else if (*flag == 1)
			*flag = 0;
	}
	else if (ptr == 31 && (*flag == 0 || *flag == 2))
	{
		if (*flag == 0)
			*flag = 2;
		else if (*flag == 2)
			*flag = 0;
	}
	return (0);
}

int	size_rd(char *ptr, char *dst)
{
	int	size;
	int	flag;

	flag = 0;
	size = 0;
	(ptr+=2);
	skipp_space(&ptr);
	while (*ptr)
	{
		if (flag == 0 && (*ptr == '|' || *ptr == '>' || *ptr == '<'
				|| *ptr == ' ' || *ptr == '\t'))
			break ;
		else if (*ptr != 30 && *ptr != 31 && flag == 0)
		{
			if(dst)
				dst[size++] = *ptr;
			else 
				size++;
		}
		else if(*ptr == 30 || *ptr == 31)
			help_red(*ptr, &flag);
		ptr++;
	}
	if (dst)
		dst[size] = '\0';
	return (size);
}

t_red	*save_rd(t_cmd*cmd ,char *ptr)
{
	int		size;
	t_red	*valeur;

	valeur = malloc(sizeof(t_red));
	if (!valeur)
		return (NULL);
	size = size_rd(ptr, NULL);
	valeur->value = malloc(sizeof(char) * (size + 1));
	if (!valeur->value)
	{
		free(valeur);
		return (NULL);
	}
	size_rd(ptr, valeur->value);
	valeur->type = 99;
	size = 1;
	file_addback(cmd ,valeur, size);
return (valeur);
}
