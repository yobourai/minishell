

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

// char *space(char *input) 
// {
//     int i = 0;
//     int  j = 0;
//     char *tmp = malloc(strlen(input) + 1);

//     if (!tmp)
//         return NULL;

//     while (input[i] == ' ' || input[i] == '\t')
//                 i++;
//     while (input[i]) 
//     {
//          if (input[i] == ' ' || input[i] == '\t')
//         {
//             if (j > 0 && tmp[j - 1] != ' ')
//                 tmp[j++] = ' ';
//         } 
//         else
//             tmp[j++] = input[i];
//         i++;
//     }

//     if (j > 0 && tmp[j - 1] == ' ')
//             j--;
//     tmp[j] = '\0';
//     return tmp;
// }


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
            (c >= '0' && c <= '9') || 
            c == '_');
}

char *dollar_sign(char *input, t_env *env)
{
    int i = 0;
    int  k = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;
    if(!input)
        return NULL;
    char *tmp = malloc(strlen(input) * 500 + 1);
    if (!tmp)
        return NULL;

    char *ptr = malloc(strlen(input) * 10 + 1);
    if (!ptr)
    {
        free(tmp);
        return NULL;
    }

    while (input[i])
    {
        if (input[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            tmp[k++] = input[i++];
        }
        else if (input[i] == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            tmp[k++] = input[i++];
        }
        else if (input[i] == '$' && !in_single_quote)
        {
            i++;
            int j = 0;
            while (input[i] && is_valid_var_char(input[i]) && input[i] != ' ')
                ptr[j++] = input[i++];
            ptr[j] = '\0';

            char *value = get_value(env, ptr);
            if (value)
            {
                while (*value)
                    tmp[k++] = *value++;
            }
            else
            {
                tmp[k++] = '$';
                int m = 0;
                while(m < j)
                    tmp[k++] = ptr[m++];
            }
        }
        else
            tmp[k++] = input[i++];
    }

    tmp[k] = '\0';
    free(ptr);
    return tmp;
}

int redairection_help(char * input)
{
    int i = 0;
    while(input[i])
    {
    

        i++;
    }
    return 0;
}
int redairectionc_error(char *input)
{
    int i = 0;
    while (input[i] == ' ' || input[i] == '\t')
        i++;
    if(input[i] == '|')
    {
        printf("syntax error near unexpected token \n");
        return 1;
    }
    while(input[i])
    {
       
        if( input[i] == '&'||(input[i] == '|' && input[i+1] == '|' ) || (input[i] == '&'  && input[i+1] == '&'))
        {
            printf("syntax error near unexpected token \n");
            return 1;
        }
        i++;
    }
    if(input[i] == '\0')
            i--;
    while(0 <= i && (input[i] == ' ' || input[i] == '\t'))
            i--;
    if(input[i] == '|' || input[i] == '>' || input[i] == '<' || ( input[i] == '>' && input[i+1] == '>') || (input[i] == '<' && input[i-1] == '<') || (input[i] == '>' && input[i-1] == '>'))
    {
        printf("syntax error near unexpected token \n");
        return 1;
    }
    if(redairection_help(input) == 1)
    {
        printf("syntax error near unexpected token \n");
        return 1;
    }
    return 0;
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