/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:20:36 by yobourai          #+#    #+#             */
/*   Updated: 2025/01/27 09:06:23 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_hp(char **ptr, t_env *env)
{
	char	*tmp;
	int		j;

	while (env)
	{
		j = 0;
		tmp = *ptr;
		while (is_valid_char(*(++tmp)) && env->name[j])
		{
			if (*tmp != env->name[j])
				break ;
			j++;
		}
		if (!env->name[j] && is_valid_char1(*tmp))
		{
			*ptr = tmp;
			return (ft_strlen(env->value));
		}
		env = env->next;
	}
	while (is_valid_char(*tmp))
		tmp++;
	*ptr = tmp;
	return (0);
}

int	size_st(char *ptr, t_env *env)
{
	int	flag;
	int	size;

	size = 0;
	flag = 0;
	skipp_space(&ptr);
	while (*ptr != '\0')
	{
		if ((*ptr == ' ' || *ptr == '\t' || *ptr == '|' || *ptr == '<'
				|| *ptr == '>') && flag == 0)
			break ;
		if (*ptr == '$' && flag != 1 && is_valid_char_first(*(ptr + 1)))
			size += size_hp(&ptr, env);
		else if (*ptr == 30 || *ptr == 31)
		{
			help_red_add(*ptr, &flag);
			(ptr)++;
		}
		else
		{
			size++;
			(ptr)++;
		}
	}
	return (size);
}

char	*cpy_hp(char **ptr, t_env *env)
{
	char	*tmp;
	int		j;

	while (env)
	{
		j = 0;
		tmp = *ptr;
		while (is_valid_char(*(++tmp)) && env->name[j])
		{
			if (*tmp != env->name[j])
				break ;
			j++;
		}
		if (is_valid_char1(*tmp) && !env->name[j])
		{
			*ptr = tmp;
			return (env->value);
		}
		env = env->next;
	}
	while (is_valid_char(*tmp))
		tmp++;
	*ptr = tmp;
	return (NULL);
}

void	copy_value_hp(char **str, char *dest, int *flag, t_env *env)
{
	char	*value;
	int		j;

	j = 0;
	while (**str != '\0')
	{
		if ((**str == ' ' || **str == '\t' || **str == '|' || **str == '>'
				|| **str == '<') && *flag == 0)
			break ;
		if (**str == '$' && *flag != 1 && is_valid_char_first(*(*str + 1)))
		{
			value = cpy_hp(str, env);
			while (value && *value)
				dest[j++] = *value++;
		}
		else if (**str == 30 || **str == 31)
		{
			help_red_add(**str, flag);
			(*str)++;
		}
		else
			dest[j++] = *(*str)++;
	}
}

char	*cpy_value(char **ptr, t_env *env, char *dest)
{
	int		flag;
	char	*str;
	int		size;

	str = *ptr;
	flag = 0;
	size = size_st(str, env);
	skipp_space(&str);
	copy_value_hp(&str, dest, &flag, env);
	*ptr = str;
	dest[size] = 0;
	return (dest);
}
