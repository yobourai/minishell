/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:19:15 by yobourai          #+#    #+#             */
/*   Updated: 2025/01/27 00:16:58 by yobourai         ###   ########.fr       */
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

int	redirection(t_bash *bash, char *src)
{
	t_red	*in;
	t_red	*out;
	t_cmd	*cmd;
	int		flag;

	flag = 1;
	cmd = bash->cmd;
	while (cmd->next)
		cmd = cmd->next;
	while (*src)
	{
		if (/*flg*/);		//*src pipe
			break ;
		else if (/*flg*/);	//*src redirection
		{
			if (flag)		//*src redirection == red_intput < input
				//	in = 
			else if (flag);	//*src redirection != here_document | flag if have error ambuguas of no sush file
				//	out = 
			else;	//*src here_document	input
				//	in = 
			//skip at end of file >file
		}
		else
			src ++;
	}
	return (flag);
}