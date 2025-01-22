#include "minishell.h"

int is_valid_char(char c)
{
    return ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || 
            c == '_');
}
void handle_error(char *data,char *message)
{
    if(data)
        free(data);
    ft_putstr_fd(message,2);
}


void free_env(t_env * env)
{
    t_env * curent;

    while (env)
    {
        curent = env->next;
        free(env->name);
        free(env->value);
        free(env);
        env = curent ;
    }
    
}

t_env	*get_env(char *env)
{
	t_env	*curent;
	int		j;

    j = 0 ;
	curent = malloc(sizeof(t_env));
    if(!curent && (handle_error(NULL,"failure allocation\n"), 1))
		return (NULL);
	while(env[j] && env[j] != '=')
		j++;
	curent->name = ft_substr(env ,0,j);
	if(!curent->name)
	{
		handle_error(NULL , "failure allocation\n");
		return (NULL);
	}
	curent->value = ft_substr(env , j+1 , ft_strlen(env));
	if(!curent->value)
	{
		free(curent->name);
		handle_error(NULL , "failure allocation\n");
		return (NULL);
	}
	curent->next = NULL;
	return (curent);
}

void	env_add_back(t_env **head, t_env *curent)
{
	t_env *env;

	if(!*head)
	{
		*head = curent;
		return ;
	}
	env = *head;
	while(env->next)
		env = env->next;
	env->next = curent;
}

t_env   *cnv_env(char **env)
{
    t_env   *head;
    t_env   *curent;
    int		i;

    i = 0;
    head = NULL;
    while (env[i])
    {
		curent = get_env(env[i]);
		if(!curent)
		{
			free_env(head);
			return (NULL);		
		}
		env_add_back(&head , curent);
        i++;
    }
    return (head);
}

t_bash *allocation(char **env)
{
    t_bash *nada;

    nada = malloc(sizeof(t_bash));
    if(!nada)
    {
        handle_error(NULL,"failure allocation\n");
        exit(1);
    }
    if (env && *env)
    {
        nada->env = cnv_env(env);
        if(!nada->env)
        {
            handle_error(NULL , "failure allocatin\n");
            exit(1);
        }
    }
    else
        nada->env = NULL;
    nada->cmd = NULL;
    nada->exit_status = 0;
    return (nada);
}

char *get_value_cpy(t_env *env, char *value)
{
    if (!value)
        return NULL;
    while (env)
    {
        if (strcmp(env->name, value) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

char *cpy_hp(char **ptr, t_env *env)
{
    char tmp[1024];
    char *value = NULL;
    int j = 0;

    (*ptr)++; 
    while (is_valid_char_first(**ptr)) 
    {
        if(!is_valid_char(**ptr))
            break;
        tmp[j++] = **ptr;
        (*ptr)++;
    }
    tmp[j] = '\0';
    value = get_value_cpy(env, tmp);
    return value;
}

char *cpy_value(char *ptr, t_env *env)
{
    int flag ;
    int size;
    char *value;
    char *result;
    char *res_ptr;
    int fambg;

    fambg = 0;
    flag = 0;
    size = size_st(ptr, env);    
    result = malloc(size + 1);
    if (!result)
        return NULL;
    res_ptr = result;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++; 
    while (*ptr != '\0')
    {
        if (*ptr == '$' && flag != 1) 
        {
            value = cpy_hp(&ptr, env);
            if (value)
            {
                while (*value)
                    *res_ptr++ = *value++;
            }
        }
        else if (*ptr == '\'' || *ptr == '"')
        {
            help_red(*ptr, &flag , &fambg);
            ptr++;
        }
        else
            *res_ptr++ = *ptr++;
    }
    *res_ptr = '\0';
    return result;
}

int handle_ambg(char *ptr)
{
    int flag;
    int fambg;

    flag = 0;
    fambg = 0;
    int i = 0;

    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    while(*ptr !='\0')
    {
        if(*ptr != '\'' && *ptr != '"' && fambg == 0)
        {
            i++;
        }
        else
        {
            help_red(*ptr , &flag , &fambg);
            ptr++;
            i++;
        }
    }
    *tmp = '\0';
    if(ft_strlen(start) == i)
    {
         printf("ambgous ==%s\n", start);
            return i;
    }        ///ambgous error
    else
    {
        free(start);
        printf("no such file\n");
        return 0;
    }   //no such file
}

t_red *save_redirection(char *ptr, t_env *env)
{
    t_red   *valeur;
    int     size;
    
    valeur = malloc(sizeof(t_red));
    if (!valeur)
        return NULL;
    set_typ(ptr, &valeur->type);
    if (valeur->type == 98)
        size = size_st(ptr + 2, env);
    else
        size = size_st(ptr + 1, env);
    if(size == 0)
    {
        if(valeur->type == 98)
            valeur->type = handle_ambg(ptr + 2);
        else
            valeur->type = handle_ambg(ptr + 1);
        printf("allocated size = %d\n", size);
        if(valeur->type == 19)
        {
            // embguaus size;
            valeur->value = malloc(size + 1);
            //  check malloc | free struct
            // cpy variable environment
        }
        else
        {
            valeur->value = malloc(sizeof(char) * 1);
            //  check malloc | free struct
        }
        valeur->value[size] = 0;
        // if(valeur->type == 98)
        //     size = handle_ambg(ptr + 2);
        // else
        //     size = handle_ambg(ptr + 1);
        // printf("allocated size = %d\n", size);
        // if(size)
        // {
        //     valeur->value = malloc(size + 1);
        //     valeur->type = 19;
        // }
        // else
        // {
        //     valeur->value = malloc(sizeof(char) * 1);
        //     valeur->type = 20;
        // }
        return valeur;
    }
    else
    {
        if (valeur->type == 98)
            valeur->value = cpy_value(ptr + 2, env);
        else
            valeur->value = cpy_value(ptr + 1, env);
        //  check malloc | free struct
        
    }
    return valeur;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
	(void)av;
    t_env *tmp = cnv_env(env);
    t_red *ptr = save_redirection("< $", tmp);
    printf("value =%s\n", ptr->value);
    printf("type = %d\n", ptr->type);
    return 0;
}