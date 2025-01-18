#include "minishell.h"

int is_valid_char(char c)
{
    return ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || 
            c == '_');
}

int is_valid_char_first(char c)
{
    return ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            c == '_');
}

void set_typ(char **ptr, int *type)
{
    if (**ptr == '<')
    {
        if (*(*ptr + 1) == '<')
            *type = 98; // Append redirection
        else
            *type = 96; // Input redirection
    }
    else if (**ptr == '>')
        *type = 97; // Output redirection

    while (**ptr == ' ' || **ptr == '\t')
        (*ptr)++;
}

char *get_value(t_env *env, char *value)
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

int dollar_sign(char *input, t_env *env)
{
    int i = 0;
    int size = 0;
    int in_single_quote = 0;

    while (input[i])
    {
        help_red(&input, &in_single_quote);
        if (input[i] == '$' && !in_single_quote)
        {
            i++;
            while (input[i] && is_valid_char(input[i]) && input[i] != ' ')
                size++;

            char *value = get_value(env, input + i);
            if (value)
            {
                size = 0;
                while (*value++)
                    size++;
            }
        }
        i++;
    }
    return size;
}

t_red *save_redirection(char *ptr, t_env *env)
{
    t_red *valeur = malloc(sizeof(t_red));
    if (!valeur)
        return NULL;

    // Initialize `type` before passing to set_typ
    valeur->type = 0;
    set_typ(&ptr, &valeur->type);

    int size = dollar_sign(ptr, env);
    (void)size; // Suppress unused variable warning if not used further

    // Additional processing if needed
    valeur->value = NULL; // Initialize value or process it properly
    return valeur;
}

int main(int ac, char **av, char **env)
{
    (void)ac; // Suppress unused parameter warning
    t_env *tmp = cnv_env(env);
    t_red *ptr = save_redirection(av[1], tmp);

    if (ptr)
    {
        printf("value == %s\n", ptr->value ? ptr->value : "(null)");
        printf("type == %d\n", ptr->type);
        free(ptr->value);
        free(ptr);
    }
    return 0;
}
