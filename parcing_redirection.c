/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:19:15 by yobourai          #+#    #+#             */
/*   Updated: 2025/01/27 17:19:40 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_redirection_hp(char *ptr, t_cmd *cmd, t_red *valeur)
{
	int		size;

	size = handle_ambg(ptr);
	if (size != 0)
	{
		printf("debug %d\n", cpy_ambg_size(ptr));
		valeur->value = malloc(sizeof(char) * (1 + cpy_ambg_size(ptr)));
		cpy_ambg(ptr, valeur->value);
		if (!valeur->value)
		{
			free(valeur);
			return ;
		}
	}
	else
	{
		valeur->value = malloc(sizeof(char) * 1);
		if (!valeur->value)
		{
			free(valeur);
			return ;
		}
		valeur->value[0] = '\0';
	}
    if (valeur->type == 97)
        size = 1;
    else
		size = 0;
	valeur->type = handle_ambg(ptr);
    file_addback(cmd, valeur, size);
}

void    file_addback(t_cmd *cmd, t_red *new, int in_out)
{
    t_red   *head;
    
    if (in_out)
    {
        head = cmd->in;
        if (!head)
        {
            printf("ff\n");
            cmd->in = new;
            return ;
        }
    }
    else
    {
        printf("ss\n");
        head = cmd->out;
        if (!head)
        {
            cmd->out = new;
            return ;
        }
    }
   while (head->next)
        head = head->next;
    head->next = new;
}

t_red	*save_redirection(char *ptr, t_env *env, int *flag , t_cmd *cmd)
{
	t_red	*valeur;
	int		size;
	
    valeur = malloc(sizeof(t_red));
	if (!valeur)
		return (NULL);
	valeur->next = NULL;
	set_typ(&ptr, &valeur->type);
	size = size_st(ptr, env);
	if (size == 0)
	{
		*flag = 1;
		save_redirection_hp(ptr, cmd, valeur);
		return (valeur);
	}
    else
	{
		valeur->value = malloc(size + 1);
	    if (!valeur->value)
		    return (free(valeur), NULL);
        valeur->value = cpy_value(&ptr, env, valeur->value);
	}
    if (valeur->type == 97)
        size = 1;
    else
        size = 0;
    file_addback(cmd, valeur, size);
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
        skipp_space(ptr);
}
int count_arg(char **src, int *quotes)
{
    int size ;
    char    *ptr;

    size = 0;
    ptr = *src;
    while(*ptr)
    {
        if (*ptr == 30 || *ptr == 31)
        {
            size++;
            help_red_add(*ptr, quotes);
        }
        if((*ptr == ' ' || *ptr == '\t' || *ptr == '>' || *ptr == '<' || *ptr == '|') && *quotes == 0)
                break;
        else
            size++;
        ptr++;
    }
    if (size)
        size = 1;
    skipp_space(&ptr);
    *src = ptr;
    return (size);
}
int  redirection(t_bash *bash, char **str, int *flag, int *quotes)
{
    t_red   *in;
    int size;
    char    *ptr;

    in = NULL;
    size = 0;
    ptr = *str;
    while (*ptr)
    {
        if (*ptr == '|' && *quotes == 0)
            break;
        else if ((*ptr == '<' || *ptr == '>') && *quotes == 0)
        {
            if (!*flag && *ptr == '>')
                in = save_redirection(ptr, bash->env, flag , bash->cmd);
            else if (!*flag && *ptr == '<' && *(ptr + 1) != '<')
            {
                in = save_redirection(ptr, bash->env, flag , bash->cmd);
                if (in && in->type == 97)
                {
                    if (access(in->value, F_OK) != 0)
					{
						in->type = 0;
                        *flag = 1;
					}
                }
            }
            else if (*ptr == '<' && *(ptr + 1) == '<')
                in = save_rd(bash->cmd , ptr);
            skip_at_end(&ptr);
        }
		else
	        size += count_arg(&ptr, quotes);
    }
    if (!size)
	{
		printf("lay \n");
        *str = ptr;
	}
    return (size);
}

t_cmd    *cmd_new(t_cmd *head)
{
    t_cmd   *tmp;
    t_cmd   *new;

    new = alloc_command();
    if (!new)
    {
        free_cmd(head);
        return (NULL);
    }
    tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (new);
}

void    print(t_cmd *cmd)
{
    t_red   *tmp;

	while (cmd)
	{
		printf("input****\n");
		tmp = cmd->in;
		while (tmp)
		{
			printf("in =>name = %s|", tmp->value);
			printf(" type = %d|\n", tmp->type);
			tmp = tmp->next;
		}
		printf("output****\n");
		tmp = cmd->out;
		while (tmp)
		{
			printf("output =>name = %s|", tmp->value);
			printf(" type = %d|\n", tmp->type);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}

int get_command_info(t_bash *bash, char *src)
{
    t_cmd *cmd;
    int flag = 0;
    int quotes = 0;
    int size;

    cmd = bash->cmd;
    while (*src)
    {
        size = redirection(bash, &src, &flag, &quotes);
        printf("**size = %d\n", size);
        // if (size)
        // {
           // save arguments
        // }
        if (*src)
        {
            cmd = cmd_new(bash->cmd);
            src++;
        }
    }
	cmd = bash->cmd;
    print(cmd);
    return flag;
}
