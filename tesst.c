#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "./libft/libft.h"
typedef struct  s_env{
    char * name ;
    char *value;
    struct s_env *next;    
} t_env ;
char *space(char *input) 
{
    int i = 0;
    int  j = 0;
    char *tmp = malloc(strlen(input) + 1);

    if (!tmp)
        return NULL;

    while (input[i] == ' ' || input[i] == '\t')
                i++;
    while (input[i]) 
    {
        if (input[i] == ' ' || input[i] == '\t')
        {
            if (j > 0 && tmp[j - 1] != ' ')
                tmp[j++] = ' ';
        } 
        else
            tmp[j++] = input[i];
        i++;
    }

    if (j > 0 && tmp[j - 1] == ' ')
            j--;

    tmp[j] = '\0';
    return tmp;
}

char *handle_quotes(char *ptr)
{
    int i = 0;
    int  k = 0;
    int in_single_quote = 0;
    int  in_double_quote = 0;
    int j = 0;
    int z = 0;
    int m = 0;
    ptr = space(ptr);
    char *tmp = malloc(strlen(ptr) + 1);
    if (!tmp)
    {
        exit(1);
    }
    while (ptr[i])
    {
        if(ptr[i] == '\'' && j != 2)
        {
            j = 1;
            z++;
            if(z % 2 == 0)
                j = 0;
        }
       else if(ptr[i] == '"' && j != 1)
       {
            j=2;
            m++;
            if(m % 2 == 0)
                j = 0;
       }
        if (ptr[i] == '\'' && !in_double_quote)
        {
            if (in_single_quote)
                in_single_quote = 0;
            else  
                in_single_quote = 1;
        }
        else if (ptr[i] == '"' && !in_single_quote)  
        {
            if (in_double_quote)
                in_double_quote = 0;
            else
                in_double_quote = 1;
        }
        else
            tmp[k++] = ptr[i];
        i++;
    }

    if ((z  % 2 != 0 && j == 1) || (m %2 != 0 && j == 2))
    {
        free(tmp);
        write(2, "syntax error near unexpected token '\n", 38);
       exit(1);
    }

    tmp[k] = '\0'; 
    return tmp;
}
void print_env(t_env *env)
{
    while(env)
    {
        printf("name == '%s'\n",env->name);
        printf("9ima == '%s'\n",env->value);
        env = env->next;
    }
}
void free_env(t_env * env)
{
    t_env * curent = NULL;
    while (env)
    {
        curent = env->next;
        free(env->name);
        free(env->value);
        free(env);
        env = curent ;
    }
    
}
t_env   *cnv_env(char **env)
{
    if(!*env)
        return NULL;
    int i = 0;
    int j = 0;
    int k = 0;
    t_env * head = NULL;
    t_env * curent = NULL;

    while (env[i])
    {
        j = 0 ;
        while(env[i][j])
        {
            if(env[i][j] == '=')
            {
                t_env *cnv = malloc(sizeof(t_env));
                cnv->name = ft_substr(env[i] ,0,j);
                cnv->value = ft_substr(env[i] , j+1 , ft_strlen(env[i]));
                cnv->next = NULL ;
                if(!head)
                    head = cnv ;
                else
                    curent->next = cnv;

                curent = cnv;
                    break;
            }
            j++;
        }        
        i++;
    }
    
    return head ;
}
char *get_value(t_env * env , char *value)
{
    if(!value)
        return NULL;
    while(env)
    {
        if(strcmp(env->name , value) == 0)
        {
            return env->value;
        }
        env = env->next;
    }
    return NULL;
}
int is_valid_var_char(char c)
{
    return ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') ||  
            c == '_');
}

char *dollar_sign(char *input, t_env *env)
{
    int i = 0;
    int  j = 0;
    int  k = 0;
    char *tmp = malloc(strlen(input) * 5000 + 1);
    if(!tmp)
        return NULL;
    char *ptr = malloc(ft_strlen(input) + 1);
    if (!ptr)
    {
        free(tmp);
        return NULL;
    }
    int z = 0;
    while (input[i])
    {
      while (input[i] && !(input[i] == '$' && (i == 0 || input[i - 1] != '\'')))
        {
            if(input[i] == '\'' )
                z++;
            tmp[k++] = input[i++];
        }

        if (input[i] == '$')
        {
            i++; 
            j = 0;

            while (input[i] && is_valid_var_char(input[i]) && z % 2 == 0)
            {
                ptr[j++] = input[i++];
            }
            ptr[j] = '\0';

            char *value = get_value(env, ptr);
            if (value)
            {
                while (*value)
                {
                    tmp[k++] = *value++;
                }
            }
            else
            {
                int m = 0;
                tmp[k++] = '$';
                while( m < j)
                    tmp[k++] = ptr[m++];
            }
        }
    }

    tmp[k] = '\0';
    free(ptr);
    return tmp;
}


char *inpute(char *input , t_env *env)
{
    int i = 0;
    char *str ;
        char *tmp;
    while (1) 
    {
        input = readline("minishell : ");
        printf("%s\n",input);
        input = dollar_sign(input , env);
       input = handle_quotes(input);
        printf("%s\n",input);
        if (input == NULL)
        {
            printf("\nExiting...\n");
            break;
        }
        add_history(input);
        free(input);
    }
    return input;
}

int main(int ac , char **av , char **env)
{
    (void)ac;
    (void)av;
    char * input ;
    t_env * anv = cnv_env(env);
    // // print_env(anv);
    input = inpute(input , anv);
    // char *value = dollar_sign(input , anv);
    //  input = get_value(anv,NULL );
    // input = inpute(input , anv);
    // input = dollar_sign(input , anv);
     printf("%s\n",input);
}