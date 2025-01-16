#include "minishell.h"
int handle_pipe(t_bash *bash, char *ptr)
{
	int i;
	int number_pip;

	number_pip = 0;
	i = 0;
    while(ptr[i])
    {
		if(ptr[i] == '|')
			number_pip++;
		else if(ptr[i] == ' ' || ptr[i] == '\t')
			number_pip = number_pip;
		else
			number_pip = 0;
		if(number_pip > 1)
			break;
		i++;
	}
	if(number_pip > 1 || (number_pip == 1 && ptr[i] == '\0'))
	{
		bash->exit_status = 1;
		ft_putstr_fd("syntax error near unexpected token |\n", 2);
		return 1;
	}
    return 0;
}
void check_qoutes(char input, int *qoutes)
{
    if (input == 31 && *qoutes == 0)
    {
        if (*qoutes == 2)
            *qoutes = 0;
        else
            *qoutes = 2;
    }
    else if (input == 30 && *qoutes == 0)
    {
        if (*qoutes == 1)
            *qoutes = 0;
        else
            *qoutes = 1;
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
	if(ptr[i] == '\0')
	{
		ft_putstr_fd("syntax error near unexpected token newline",2);
		return 1;
	}
    if (ptr[i] == ptr[i+1])
		i++;
	i++;
	while (ptr[i] == ' ' || ptr[i] == '\t')
		i++;
	if (ptr[i] == '\0' || ptr[i] == '>' || ptr[i] == '<' || ptr[i] == '|')
	{
		if(ptr[i] == '\0')
			ft_putstr_fd("syntax error near unexpected token newline\n",2);
    	else if (ptr[i] == '>')
			ft_putstr_fd("syntax error near unexpected token <\n",2);
    	else if (ptr[i] == '<')
        	ft_putstr_fd("syntax error near unexpected token <\n",2);
		else if ((ptr[i] == '|'))
			ft_putstr_fd("syntax error near unexpected token |\n",2);
		return 1;
	}
	return 0;
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
        if ((ptr[i] == '>' || ptr[i] == '<') && error_red(ptr+i))
        {
            bash->exit_status = 1;
            return 1;
        }
        i++;
    }
    return 0;
}
