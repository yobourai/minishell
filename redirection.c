#include "minishell.h"

void check_qoutes(char input, int *qoutes)
{
    if (input == 31 && *quotes == 0)
    {
        if (*quotes == 2)
            *quotes = 0;
        else
            *quotes = 2;
    }
    else if (input == 30 && *quotes == 0)
    {
        if (*quotes == 1)
            *quotes = 0;
        else
            *quotes = 1;
    }
}

int skip_red(char *ptr, int *qoutes)
{
    int i;


    i = 1;
    while(ptr[i] && ptr[i] != ptr[0])
        i++;
    *qoutes = 0;
    return i;
}

int error_red(char *ptr)
{
    int i;

    i = 0;
    if(ptr[1] == ptr[0])
        i++;
    while (ptr[i] == ' ' || ptr[i] == '\t')
        i++;
      if(input[i] == '>' && input[i+1] == ' ' && input[i+2] == '>')
            return 1;
      if(input[i] == '<' && input[i+1] == ' ' && input[i+2] == '<')
            return 1;
      if((input[i] == '>' && input[i+1] == '<' ) || (input[i] == '>' && input[i+1] == ' ' && input[i+2] == '<'))
            return 1;
      if((input[i] == '>' && input[i+1] == '>' && input[i+2] == ' ' && input[i+3] == '>') || (input[i] == '>' && input[i+1] == '>' && input[i+2] == '>'))
            return 1;
      if((input[i] == '<' && input[i+1] == '<' && input[i+2] == ' ' && input[i+3] == '<'))
            return 1;
      if(input[i] == '|' && input[i+1] == ' ' && input[i+2] == '|')
            return 1;
      if((input[i] == '|' && input[i+1] == ' ' && input[i+2] == '<' && input[i+3] == '<') || (input[i] == '|' &&input[i+1] == '<' && input[i+2] == '<'))
            return 1;
      if((input[i] == '>' && input[i+1] == ' ' && input[i+2] == '|' ) || (input[i] == '>' &&input[i+1] == '>' && input[i+2] == '|'))
            return 1;
      if((input[i] == '<' && input[i+1] == ' ' && input[i+2] == '|' ) || (input[i] == '<' &&input[i+1] == '<' && input[i+2] == '|'))
            return 1;
      if(input[i] == '<' && input[i+1] =='|')
            return 1;
    
}

int handel_redirection(t_bash *bash, char *ptr)
{
    int quotes;
    int i;

    i = 0;
    while(ptr[i])
    {
        quotes = 0;
        check_qoutes(ptr[i] , &quotes);
        if(quotes)
           quotes = skip_red(&ptr[i] , &quotes);
        i += quotes;
        if ((ptr[i] == '>' || ptr[i] == '<') && error_red(ptr))
        {
            bash->exit_status = 1;
            return 1;
        }
        i++;
    }
    return 0;
}
