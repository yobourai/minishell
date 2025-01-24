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

int  help_red_add(char ptr , int *flag , int *fambg)
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

int size_hp(char **ptr, t_env *env , int *flag )
{
    char    *tmp;
    int     j;
    int i ;
    i  = 0;
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
       if ((*tmp== ' ' || *tmp == '\t' || *tmp == '|' || *tmp == '<' || *tmp == '>' )&& !env->name[j] && *flag == 0)
        {
            *ptr = tmp;
            return (ft_strlen(env->value));
        }
        env = env->next;
    }
    while (*tmp)
        {
            if((*tmp == ' ' || *tmp == '\t' || *tmp == '|' || *tmp == '<' || *tmp == '>') && *flag == 0)
                break;
            i++;
            tmp++;
        }
    *ptr = tmp;
    return i+1;
}

int size_st(char *ptr, t_env *env)
{
    int flag ;
    int size;
    int famg;
    int k;

    famg = 0;
    size = 0;
    flag = 0;
    k = 0;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    while (*ptr != '\0')
    {
        if((*ptr == ' ' || *ptr == '\t' || *ptr == '|' || *ptr == '<' || *ptr == '>') && flag == 0)
                break;
		if(*ptr == '$'&& flag != 1 && is_valid_char_first(*(ptr + 1)))
            size+=size_hp(&ptr, env , &flag);
        else if(*ptr == '\'' || *ptr == '"')
        {
			help_red_add(*ptr ,&flag ,&famg);
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

char *cpy_hp(char **ptr, t_env *env , char *dest , int *flag)
{
    char    *tmp;
    int     i = 0;
    int     j;

    printf("ptr12=%s\n",dest);
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
        if ((*tmp== ' ' || *tmp == '\t' || *tmp == '|' || *tmp == '<' || *tmp == '>' )&& !env->name[j] && *flag == 0)
        {
            *ptr = tmp;
            strcpy(dest , env->value);
            return (dest); 
        }
        env = env->next;
    }
    dest[0] = '$';
    // while(tmp[i])
    // {
    //     dest[i+1] = tmp[i];
    //     i++;
    // }
    *ptr = tmp;
    return dest;
}

char *cpy_value(char **ptr, t_env *env , char *dest)
{

    int flag;
    char *str;
    char *value;
    str = *ptr;
    str++;
    if (*str == '>')
        str++;
    flag = 0;
    while (*str == ' ' || *str == '\t')
        (str)++;
    while (*str != '\0')
    {
        if((*str == ' ' || *str == '\t' || *str == '|' || *str == '>' || *str == '<') && flag == 0)
                break;
		if(*str == '$'  && flag != 1 && is_valid_char_first(*(str + 1)))
        {
            value= cpy_hp(&str, env , dest , &flag);
            if(value)
            {
               strcpy(dest , value);
                printf("ccc\n");
            }
        }
        else if (*str == '\'' || *str == '"')
        {
            help_red_add(*str, &flag ,0);
            (str)++;
        }
        else
            *dest++ = *str++;
    }
    printf("dest ==%s\n",dest);
    *ptr = str;

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
        help_red_add(*ptr, &flag, &fambg);
        if(fambg == 1)
            return 0;//no such file
        if ((*ptr == '|' || *ptr == '>' || *ptr == '<' || *ptr == ' ' || *ptr == '\t') && flag == 0)
                break;
            ptr++;
            size++;
    }
    i = size -1;
    return i;//ambgous error
}
char *cpy_ambg(char *ptr)
{
    int size;
    char *tmp;
    int i = 0;
    int j = 0;
    size = handle_ambg(ptr);
	int flag;
	int famg;
    while (ptr[i] == ' ' || ptr[i] == '\t')
        i++;
    tmp = malloc(size +2);
    if(!tmp)
        return NULL;
    while(ptr[i] !='\0')
    {
		help_red_add(*ptr, &flag, &famg);
        if ((ptr[i] != '|' && ptr[i] != '>' && ptr[i] != '<' && ptr[i] != ' ') || flag == 1)
                tmp[j++] = ptr[i++];
            else
                return tmp;
    }
    return tmp;
}

t_red *save_redirection(char *ptr, t_env *env)
{
    t_red   *valeur;
    int     size;
    int		flag; 

    valeur = malloc(sizeof(t_red));
    if (!valeur)
        return NULL;
    set_typ(ptr, &valeur->type);
    if (valeur->type == 98)
        size = size_st(ptr + 2, env);
    else
        size = size_st(ptr + 1, env);
	printf("size == %d\n",size);
    if(size == 0)
    {
        flag = valeur->type;
        if(valeur->type == 98)
            valeur->type = handle_ambg(ptr + 2);
        else
            valeur->type = handle_ambg(ptr + 1);
        if(valeur->type != 0)
        {
            // embguaus size;
            size = valeur->type +1 ;
            valeur->type = -1;
			if(flag == 98)
            	valeur->value = cpy_ambg(ptr + 2);
			else
            	valeur->value = cpy_ambg(ptr + 1);
            // cpy variable environment
            if(!valeur->value)
            {
                free(valeur);
                return NULL;
            }
        }
        else
        {
            valeur->value = malloc(sizeof(char) * 1);
            if(!valeur->value)
            {
                free(valeur);
                return NULL;
            }
        }
        valeur->value[size] = '\0';
		printf("valeur =%s\n", valeur->value);
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
    t_red *ptr = save_redirection("> cccaa$USER [vvv@]|$dfg", tmp);
    printf("value =%s\n", ptr->value);
    printf("type = %d\n", ptr->type);
    return 0;
}