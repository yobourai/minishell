#include "minishell.h"

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

int  help_red_add(char ptr , int *flag)
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
    char    *tmp;
    int     j;
 
    while (env)
    {
        j= 0;
        tmp = *ptr;
        while (is_valid_char(*(++tmp)) && env->name[j]) 
        {
            if (*tmp != env->name[j])
                break ;
            j++;
        }
       if (!env->name[j] && is_valid_char1(*tmp))
        {
            *ptr = tmp;
            return (ft_strlen(env->value));
        }
        env = env->next;
    }
    while (is_valid_char(*tmp))
            tmp++;
    *ptr = tmp;
    return 0;
}

int size_st(char *ptr, t_env *env)
{
    int flag ;
    int size;

    size = 0;
    flag = 0;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    while (*ptr != '\0')
    {
        if((*ptr == ' ' || *ptr == '\t' || *ptr == '|' || *ptr == '<' || *ptr == '>') && flag == 0)
                break;
		if(*ptr == '$'&& flag != 1 && is_valid_char_first(*(ptr + 1)))
            size+=size_hp(&ptr, env);
        else if(*ptr == '\'' || *ptr == '"')
        {
			help_red_add(*ptr ,&flag);
            (ptr)++;
        }
        else
        {
            size++;
            (ptr)++;
        }
    }
    return size;
}

char *cpy_hp(char **ptr, t_env *env)
{
    char    *tmp;
    int     j;

    while (env)
    {
        j= 0;
        tmp = *ptr;
        while (is_valid_char(*(++tmp)) && env->name[j]) 
        {
            if (*tmp != env->name[j])
                break ;
            j++;
        }
        if (is_valid_char1(*tmp) && !env->name[j])
        {
            *ptr = tmp;
            return (env->value); 
        }
        env = env->next;
    }
    while(is_valid_char(*tmp))
            tmp++;
    *ptr = tmp;
    return NULL;
}

char *cpy_value(char **ptr, t_env *env , char *dest)
{
    int flag;
    char *str;
    char *value;
    int j;
 
    str = *ptr;
    j = 0;
    flag = 0;
    while (*str == ' ' || *str == '\t')
        (str)++;
    while (*str != '\0')
    {
        if((*str == ' ' || *str == '\t' || *str == '|' || *str == '>' || *str == '<') && flag == 0)
                break;
		if(*str == '$'  && flag != 1 && is_valid_char_first(*(str + 1)))
        {
            value= cpy_hp(&str, env);
            if(value)
            {
                while(*value)
                    dest[j++]=*value++;
            }
        }
        else if (*str == '\'' || *str == '"')
        {
            help_red_add(*str, &flag);
            (str)++;
        }
        else
            dest[j++] = *str++;
    }
    *ptr = str;
    dest[j] = 0;
    return dest;
}

int handle_ambg(char *ptr)
{
    int flag;
    int fambg;
    int i ;
    int size;

    size = 0;
    flag = 0;
    fambg = 0;
    i = 0;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    while(*ptr !='\0')
    {
        if (*ptr == '$' && is_valid_char(*(ptr + 1)))
            ptr++;
        else if (*ptr == ' ' || *ptr == '\t' || *ptr == '|' || *ptr == '>' || *ptr == '<')
            break ; 
        else if(*ptr == '\'' || *ptr == '"' || is_valid_char1(*ptr) == 1)
            return 0;//no such file
        ptr++;
    }
    return 1;//ambgous error
}
char *cpy_ambg(char *ptr)
{
    char *tmp;
	int flag;
    int size = 0;
    int i = 0;

    flag = 0;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    while(ptr[i] !='\0')
    {
        if (ptr[i] == '\'' || ptr[i] == '"')
            help_red_add(*ptr, &flag);
        if ((ptr[i] == '|' || ptr[i] == '>' || ptr[i] == '<' || ptr[i] == ' ') && flag == 0)
            break ;
        else
            size++;
        i++;
    }
    tmp = malloc(size + 1);
    if(!tmp)
        return NULL;
    i = 0;
    size = -1;
    while(ptr[i] !='\0')
    {
        if (ptr[i] == '\'' || ptr[i] == '"')
            help_red_add(*ptr, &flag);
        if ((ptr[i] == '|' || ptr[i] == '>' || ptr[i] == '<' || ptr[i] == ' ') && flag == 0)
            break ;
        else
            tmp[++size] = ptr[i];
        i++;
    }
    tmp[size + 1] = 0;
    return tmp;
}

t_red *save_redirection(char *ptr, t_env *env)
{
    t_red   *valeur;
    int     size;

    valeur = malloc(sizeof(t_red));
    if (!valeur)
        return NULL;
    set_typ(&ptr, &valeur->type);
    size = size_st(ptr, env);
    printf("size=%d\n",size);
    if(size == 0)
    {
        valeur->type = handle_ambg(ptr);
        if(valeur->type != 0)
        {
            valeur->value = cpy_ambg(ptr);
            if(!valeur->value)
            {
                free(valeur);
                return NULL;
            }
        }
        else
        {
            valeur->type = 0;
            valeur->value = malloc(sizeof(char) * 1);
            if(!valeur->value)
            {
                free(valeur);
                return NULL;
            }
        }
        valeur->value[size] = '\0';
        return valeur;
    }
    valeur->value = malloc(size + 1);

    if(!valeur->value)
    {
        free(valeur);
        return NULL;
    }
    valeur->value = cpy_value(&ptr, env , valeur->value);
    valeur->value[size] = '\0';
    return valeur;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
	(void)av;
    t_env *tmp = cnv_env(env);
    t_red *ptr = save_redirection("> ss$USER$$HOME", tmp);
    printf("value =%s\n", ptr->value);
    printf("type = %d\n", ptr->type);
    return 0;
}