/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:19:15 by yobourai          #+#    #+#             */
/*   Updated: 2025/01/27 15:24:24 by yobourai         ###   ########.fr       */
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
	*flag = 0;
	valeur = malloc(sizeof(t_red));
	if (!valeur)
		return (NULL);
	set_typ(&ptr, &valeur->type);
	size = size_st(ptr, env);
	if (size == 0)
	{
		free(valeur);
		*flag = 1;
		return (save_redirection_hp(ptr, env));
	}
	valeur->value = malloc(size + 1);
	if (!valeur->value)
		return (free(valeur), NULL);
	valeur->value = cpy_value(&ptr, env, valeur->value);
	valeur->value[size] = '\0';
	return (valeur);
}

void	skip_at_end(char **ptr)
{
        int flag;

        flag = 0;
        if((**ptr == '<' && *(*ptr + 1) == '<' ) || (**ptr == '>' && *(*ptr +1) == '>'))
                (*ptr)+=2; 
        else
                (*ptr)++;
        skipp_space(ptr);
        while(*ptr && **ptr)
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
		 cmd = cmd->next;
    while (*src)
    {
		if(*src == 30 || *src == 31)
        	help_red_add(*src,&quotes);
        if (*src == '|' && quotes == 0)
            break;
        else if ((*src == '<' || *src == '>') && quotes == 0)
        {
            if (*src == '>' && ambg == 0 && *(src + 1) != '>')
					in = save_redirection(src ,bash->env , &ambg);
			else if ( *src == '>' && *(src + 1) == '>' && ambg == 0)
				   in = save_redirection(src ,bash->env , &ambg);
            else if (*src == '<' && *(src + 1) != '<' && ambg == 0)
			{
				   out = save_redirection(src ,bash->env , &ambg);
				   if (out->type == 97 )
					{		
						if(access(out->value,F_OK) == -1)
						{	
							flag = 0;
							printf("%s: No such file or directory \n",out->value);
							return flag;
						}
					}			
			}
            else if (flag && *src == '<' && *(src + 1) == '<' && ambg == 0)
					in = save_rd(src);
    	    skip_at_end(&src);
        }
        else
            src++;
	}
	
if (ambg == 1)
    flag = 0;
return (flag);

}
