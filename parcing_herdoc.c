#include "minishell.h"

int  help_red(char ptr , int *flag)
{
    if (ptr == '\'' && (*flag == 0 || *flag == 1)) 
    {
        if (*flag == 0)
            *flag = 1;
        else if (*flag == 1)
            *flag = 0; 
    }
    else if (ptr == '"' && (*flag == 0 || *flag == 2))
    {
        if (*flag == 0)
            *flag = 2;
        else if (*flag == 2)
            *flag = 0; 
    }
    return 0;
}

int size_rd(char *ptr, char *dst)
{
    int size;
    int flag;

    flag = 0;
    size = 0;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    while (*ptr)
    {
        if (flag == 0 && (*ptr == '|' || *ptr == '>' || *ptr == '<' || *ptr == ' '))
            break;
        else if(*ptr != '\'' && *ptr != '"')
        {
            if(dst)
                dst[size] = *ptr;
            size++;
        }
        else 
            help_red(*ptr ,&flag);
        ptr++;
    }
    if(dst)
        dst[size] = '\0';
    return size;
}

t_red *save_rd(char *ptr)
{
    int size;
    t_red *valeur;

    valeur = malloc(sizeof(t_red));
    if (!valeur)
        return NULL;

    size = size_rd(ptr + 2 , NULL);
    valeur->value = malloc(sizeof(char) * (size + 1));
    if (!valeur->value)
    {
        free(valeur);
        return NULL;
    }

    size_rd(ptr + 2, valeur->value);
    valeur->type = 99;

    return valeur;
}

