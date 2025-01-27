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

t_red	*save_redirection(char *ptr, t_env *env,int *flag)
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
		*flag = 0;
		return (save_redirection_hp(ptr, env));
	}
	valeur->value = malloc(size + 1);
	if (!valeur->value)
		return (free(valeur), NULL);
	valeur->value = cpy_value(&ptr, env, valeur->value);
	valeur->value[size] = '\0';
	return (valeur);
}

void    skip_at_end(char **ptr)
{
        int flag;

        flag = 0;
        if(**ptr == '<' && *(*ptr + 1) == '<')
                (*ptr)+=2; 
        else
                (*ptr)++;
        skipp_space(ptr);
        while(*ptr)
        {
                if((**ptr == '|' || **ptr == '>' || **ptr == '<' || **ptr == ' ' || **ptr =='\t') && flag == 0)
                        break;
                help_red_add(**ptr , &flag);
                (*ptr)++;
        }
}
int     redirection(t_bash *bash, char *src)
{
    t_red   *in = NULL;
    t_red   *out = NULL;
    t_cmd   *cmd;
   	int             flag;
    int quotes ;
    int ambg;
    ambg = 0;
	quotes = 0;
    flag = 1;
    cmd = bash->cmd;
	cmd->next = NULL;
    while (cmd->next)
    {
		 cmd = cmd->next;
	}
	printf("ff\n");

    while (*src)
    {
        help_red_add(*src,&quotes);
        if (*src == '|' && quotes == 0)         //*src pipe
            break ;
        else if ((*src == '<' || *src == '>') && quotes == 0)   //*src redirection
        {
            if (*src == '<' && ambg == 0)           //*src redirection == red_intput < input
                in = save_redirection(src ,bash->env , &ambg);
            else if (flag && *src == '>' && *src +1 != '>' && ambg == 0)    //*src redirection != here_document | flag if have error ambuguas of no sush file
                out = save_redirection(src ,bash->env , &ambg);
            else    //*src here_document    input
            	in = save_rd(src);
            skip_at_end(&src);
        }
        else
            src++;
	}
if (in)
    cmd->in = in;

if (out)
    cmd->out = out;

if (cmd->in)
    printf("in = %s\n", cmd->in->value);

if (cmd->out)
    printf("out = %s\n", cmd->out->value);

if (ambg == 1)
    flag = 0;

return (flag);

}