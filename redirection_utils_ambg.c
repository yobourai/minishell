/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_ambg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:20:53 by yobourai          #+#    #+#             */
/*   Updated: 2025/01/26 05:36:45 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_ambg(char *ptr)
{
	skipp_space(&ptr);
	while (*ptr != '\0')
	{
		if (*ptr == '$' && is_valid_char(*(ptr + 1)))
			ptr++;
		else if (*ptr == ' ' || *ptr == '\t' || *ptr == '|' || *ptr == '>'
			|| *ptr == '<')
			break ;
		else if (*ptr == 30 || *ptr == 31 || is_valid_char1(*ptr) == 1)
			return (0);
		ptr++;
	}
	return (1);
}

int	cpy_ambg_size(char *ptr)
{
	int	flag;
	int	size;
	int	i;

	i = 0;
	size = 0;
	flag = 0;
	skipp_space(&ptr);
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 30 || ptr[i] == 31)
			help_red_add(*ptr, &flag);
		if ((ptr[i] == '|' || ptr[i] == '>' || ptr[i] == '<' || ptr[i] == ' ')
			&& flag == 0)
			break ;
		else
			size++;
		i++;
	}
	return (size);
}

int	condition(char **ptr, int *flag)
{
	if ((**ptr == '|' || **ptr == '>' || **ptr == '<' || **ptr == ' ')
		&& flag == 0)
		return (1);
	return (0);
}

void	cpy_ambg(char *ptr, char *dst)
{
	int		flag;
	int		size;
	int		tootal;
	int		i;

	i = 0;
	size = 0;
	tootal = cpy_ambg_size(ptr);
	skipp_space(&ptr);
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 30 || ptr[i] == 31)
			help_red_add(*ptr,  &flag);
		if ((*ptr == '|' || *ptr == '>' || *ptr == '<' || *ptr == ' ')
			&& flag == 0)
			break ;
		else
		{
			printf("size = %d\n", size);
			dst[size] = ptr[i];
			size++;
			if (tootal == size)
				break ;
		}
		i++;
	}
	dst[size] = 0;
	printf("dd = %s\n", dst);
}
