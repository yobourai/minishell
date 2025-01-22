#include <minishell.h>


int is_valid_char_first(char c)
{
    return ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            c == '_');
}

int get_value(t_env *env, char *value)
{
    if (!value)
        return 0;
    while (env)
    {
        if (strcmp(env->name, value) == 0)
        {
            return ft_strlen(env->value);
        }
        env = env->next;
    }
    return 0;
}

int  help_red(char ptr , int *flag , int *fambg)
{
    *fambg = 0;
    if (ptr == '\'' && (*flag == 0 || *flag == 1)) 
    {
        *fambg = 1;
        if (*flag == 0)
            *flag = 1;
        else if (*flag == 1)
            *flag = 0; 
    }
    else if (ptr == '"' && (*flag == 0 || *flag == 2))
    {
        *fambg = 1;
        if (*flag == 0)
            *flag = 2;
        else if (*flag == 2)
            *flag = 0; 
    }
    return 0;
}

int size_hp(char **ptr, t_env *env)
{
    int size;
    int j;
    char tmp[1024];

    size = 0;
    j= 0;
    (*ptr)++;
    while (is_valid_char_first(**ptr)) 
    {
        if(!is_valid_char(**ptr))
            break;
        tmp[j++] = **ptr;
        (*ptr)++;
    }
    tmp[j] = '\0';
    size += get_value(env, tmp);
    return size ;
}

int size_st(char *ptr, t_env *env)
{
    int flag ;
    int size;
    int famg;

    famg = 0;
    size = 0;
    flag = 0;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    while (*ptr != '\0')
    {
		if(*ptr == '$' && flag != 1)
        {
            size += size_hp(&ptr, env);
            if(size == 0)
                return 0;
        }
        else if(*ptr == '\'' || *ptr == '"')
        {
			help_red(*ptr ,&flag , &famg);
            (ptr)++;
        }
        else
        {
            (ptr)++;
            size++;
        }
    }
    return size;
}

void set_typ(char *ptr, int *type)
{
    if (*ptr == '>')
    {
        if (*(ptr + 1) == '>')
            *type = 98;
        else
            *type = 96;
    }
    else if (*ptr == '<')
        *type = 97;
}
