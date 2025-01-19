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
			printf("env->value == %s\n",env->value);
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


int size_st(char *ptr, t_env *env)
{
    int flag = 0;
    int size = 0;
	char *tmp;
	int j = 0;
    int i = 0;
    printf("ptr==> %s\n",ptr);
    while (ptr[i] == ' ' || ptr[i] == '\t')
            i++;
    while (ptr[i] != '\0')
    {
		if(ptr[i] != '\'' && ptr[i] != '"')
		{
        
        	if (ptr[i] == '$' && flag != 1)
        	{
					 i++;
                     j= 0;
                while (is_valid_char(ptr[i])) 
                            tmp[j++] = ptr[i++];
                    
                tmp[j] = '\0';
                size += get_value(env, tmp);
			}
        	else
            {
                i++;
				size++;
            }
		}
		else 
		{
			help_red(ptr[i] ,&flag);
            i++;
		}
    }
    return size;
}

t_red *save_redirection(char *ptr, t_env *env)
{
    t_red *valeur = malloc(sizeof(t_red));
    if (!valeur)
        return NULL;
    set_typ(&ptr, &valeur->type);
    printf("type = %d\n", valeur->type);
    int size;
    if(valeur->type == 98)
        size = size_st(ptr +2, env);
    else
        size = size_st(ptr +1, env);
    printf("size = %d\n", size);
    printf("value = %s\n", valeur->value);
    // if (!valeur->value)
    // {
    //     free(valeur);
    //     return NULL;
    // }
    // valeur->value[0] = '\0';

    return valeur;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
	(void)av;
    t_env *tmp = cnv_env(env);
    t_red *ptr = save_redirection(">> $USERUSddER$USER", tmp);
        // printf("value = %s\n", ptr->value);
        // printf("type = %d\n", ptr->type);
    return 0;
}

