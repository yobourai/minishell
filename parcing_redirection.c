/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:19:15 by yobourai          #+#    #+#             */
/*   Updated: 2025/01/26 05:19:17 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red	*save_redirection_hp(char *ptr, t_env *env)
{
	t_red	*valeur;
	int		size;

	valeur = malloc(sizeof(t_red));
	if (!valeur)
		return (NULL);
	size = size_st(ptr, env);
	valeur->type = handle_ambg(ptr);
	if (valeur->type != 0)
	{
		valeur->value = cpy_ambg(ptr);
		if (!valeur->value)
			return (free(valeur), NULL);
		valeur->value[size] = '\0';
	}
	else
	{
		valeur->type = 0;
		valeur->value = malloc(sizeof(char) * 1);
		if (!valeur->value)
			return (free(valeur), NULL);
		valeur->value[0] = '\0';
	}
	return (valeur);
}

t_red	*save_redirection(char *ptr, t_env *env)
{
	t_red	*valeur;
	int		size;

	valeur = malloc(sizeof(t_red));
	if (!valeur)
		return (NULL);
	set_typ(&ptr, &valeur->type);
	size = size_st(ptr, env);
	if (size == 0)
	{
		free(valeur);
		return (save_redirection_hp(ptr, env));
	}
	valeur->value = malloc(size + 1);
	if (!valeur->value)
		return (free(valeur), NULL);
	valeur->value = cpy_value(&ptr, env, valeur->value);
	valeur->value[size] = '\0';
	return (valeur);
}

// int main(int ac, char **av, char **env)
// {
//     (void)ac;
// 	(void)av;
//     t_env *tmp = cnv_env(env);
//     t_red *ptr = save_redirection(">  ''$USEvR", tmp);
//     printf("value =%s\n", ptr->value);
//     printf("type = %d\n", ptr->type);
//     return (0);
// }
