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

int is_valid_char_first(char c)
{
    return ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            c == '_');
}

void set_typ(char **ptr, int *type)
{
    if (**ptr == '>')
    {
        if (*(*ptr + 1) == '>')
        {
            *type = 98;
        }
        else
        {
            *type = 96;
        }
    }
    else if (**ptr == '<')
    {
        *type = 97;
    }
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


int size_hp(char **ptr, t_env *env)
{
    int size;
    int j;
    char tmp[1024];

    size = 0;
    j = 0;
  
        j= 0;
        (*ptr)++;
        while (is_valid_char(**ptr)) 
         {
             tmp[j++] = **ptr;
             (*ptr)++;
         }
        tmp[j] = '\0';
        size += get_value(env, tmp);
        if(size == 0)
            size = ft_strlen(tmp) +1;
    return size ;
}

int size_st(char *ptr, t_env *env)
{
    int flag ;
    int size;

    size = 0;
    flag = 0;
    while (*ptr == ' ' || *ptr == '\t')
            (ptr)++;
    while (*ptr != '\0')
    {
		if(*ptr == '$' && flag != 1)
              size += size_hp(&ptr , env);
        else if(*ptr == '\'' || *ptr == '"')
        {
			help_red(*ptr ,&flag);
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
        if(is_valid_char(ptr))
            break;
        tmp[j++] = **ptr;
        (*ptr)++;
    }
    tmp[j] = '\0';

    value = get_value_cpy(env, tmp);
    if (!value)
      {
        value = malloc(ft_strlen(tmp) + 2);
        if (!value)
            return NULL;
        value[0] = '$';
        strcpy(value + 1, tmp);
      }
    return value; 
}

char *cpy_value(char *ptr, t_env *env)
{
    int flag ;
    int size;
    char *value;
    char *result;
    char *res_ptr;

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
            help_red(*ptr, &flag);
            ptr++;
        }
        else
            *res_ptr++ = *ptr++;
    }
    *res_ptr = '\0';
    return result;
}

t_red *save_redirection(char *ptr, t_env *env)
{
    int size;
    
    t_red *valeur = malloc(sizeof(t_red));
    if (!valeur)
        return NULL;
    set_typ(&ptr, &valeur->type);
    if (valeur->type == 98)
        size = size_st(ptr + 2, env);
    else
        size = size_st(ptr + 1, env);
     if (valeur->type == 98)
        valeur->value = cpy_value(ptr + 2, env);
    else
       valeur->value = cpy_value(ptr + 1, env);
    if (!valeur->value)
    {
        free(valeur);
        return NULL;
    }
    return valeur;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
	(void)av;
    t_env *tmp = cnv_env(env);
    t_red *ptr = save_redirection(">> $USEdfdf$USEddR $USEkR", tmp);
        printf("value = %s\n", ptr->value);
        printf("type = %d\n", ptr->type);
    return 0;
}

