#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minishell.h"
// int size_rd(char *ptr)
// {
//     int size = 0;
//     int flag = 0;
//     while (*ptr == ' ' || *ptr == '\t')
//         ptr++;

//     while (*ptr )
//     {
//         if (flag == 0 && (*ptr == '|' || *ptr == '>' || *ptr == '<' || *ptr == ' '))
//             break; 

//         if (*ptr == '\'' && (flag == 0 || flag == 1)) 
//         {
//             if (flag == 0)
//                 flag = 1;
//             else if (flag == 1)
//                 flag = 0; 
//         }
//         else if (*ptr == '"' && (flag == 0 || flag == 2))
//         {
//             if (flag == 0)
//                 flag = 2;
//             else if (flag == 2)
//                 flag = 0; 
//         }
//         else 
//             size++;

//         ptr++;
//     }
//     printf("size == %d\n", size);
//     return size;
// }
int  help_red(char **ptr , int *flag)
{
        if (**ptr == '\'' && (*flag == 0 || *flag == 1)) 
        {
            if (*flag == 0)
                *flag = 1;
            else if (*flag == 1)
                *flag = 0; 
        }
        else if (**ptr == '"' && (*flag == 0 || *flag == 2))
        {
            if (*flag == 0)
                *flag = 2;
            else if (*flag == 2)
                *flag = 0; 
        }
    if(flag != 0)
        return 1;
}

int size_rd(char *ptr, char *dst , int cpy)
{
    int size;
    int flag;

    flag = 0;
    size = 0;
    if(cpy == 0)
        (void)dst;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    while (*ptr )
    {
        if (flag == 0 && (*ptr == '|' || *ptr == '>' || *ptr == '<' || *ptr == ' '))
            break;
        else if(help_red(&ptr , &flag))
                flag = flag;
        else
        {
            if(cpy == 1)
                dst[size] = *ptr;
            size++;
        }
        ptr++;
    }
    if(cpy == 1)
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

    size = size_rd(ptr + 2 , NULL , 0);
    valeur->value = malloc(sizeof(char) * (size + 1));
    if (!valeur->value)
    {
        free(valeur);
        return NULL;
    }

    size_rd(ptr + 2, valeur->value , 1);
    valeur->type = 99;

    return valeur;
}

int main(int ac , char **av)
{
    t_red *ptr = save_rd(*(av+1));

    printf("value == %s\n", ptr->value); 
    printf("type == %d\n", ptr->type);

    free(ptr->value);
    free(ptr);

    return 0;
}

