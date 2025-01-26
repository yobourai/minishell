#include "minishell.h"

void set_typ(char **ptr, int *type)
{
    if (**ptr == '>')
    {
        if (*(*ptr + 1) == '>')
        {
            (*ptr)++;
            *type = 98;
        }
        else
            *type = 96;
    }
    else if (**ptr == '<')
        *type = 97;
    (*ptr)++;
}
int is_valid_char_first(char c)
{
    return ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            c == '_');
}

int is_valid_char(char c)
{
    return ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            (c >= '0' && c <= '9') ||
            c == '_');
}

int is_valid_char1(char c)
{
    if ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            (c >= '0' && c <= '9') ||
            c == '_')
        return  (0);
    return (1);
}

void skipp_space(char **ptr)
{
    while (**ptr == ' ' || **ptr == '\t')
        (*ptr)++;
}

int  help_red_add(char ptr , int *flag)
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
    return 0;
}
