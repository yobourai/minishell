#include "minishell.h"

int check_quotes_errors(char *input, int *single_quotes, int *double_quotes)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' && *single_quotes == 0)
		{
			if (*double_quotes == 1)
				*double_quotes = 0;
			else
				*double_quotes = 1;
		}
		else if (input[i] == '\'' && *double_quotes == 0)
		{
			if (*single_quotes == 1)
				*single_quotes = 0;
			else
				*single_quotes = 1;
		}
		i++;
	}
	if (*double_quotes == 1 || *single_quotes == 1)
		return (handle_error(NULL," syntax error near unexpected token "),1);
	return 0;
}

void truck(char *input)
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	while (input[i])
	{
		if (input[i] == '"' && (quotes == 0 || quotes == 2 ))
		{
			input[i] = 31;
			if (quotes == 2)
				quotes = 0;
			else
				quotes = 2;
		}
		else if (input[i] == '\'' && (quotes == 0 || quotes == 1))
		{
			input[i] = 30;
			if (quotes == 1)
				quotes = 0;
			else
				quotes = 1;
		}
		i++;
	}
}

void remove_unprint(char *ptr)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(ptr[i])
	{
		if(ptr[i] >=1 && ptr[i] <= 31 && ptr[i] != '\t')
			i++;
		else if(i != j)
			ptr[j] = ptr[i];
		i++;
		j++;
	}
	while(ptr[j])
		ptr[j++] = '\0';
	truck(ptr);
}
int check_pipe(char *ptr)
{
	int i;
	i = 0;
	while(ptr[i] == ' ' || ptr[i] == '\t')
		i++;
	if(ptr[i] == '|')
	{
		handle_error(NULL , "syntax error near unexpected token |\n");
		return (1);
	}
	return (0);
}

int	handle_quotes(t_bash *bash, char *ptr)
{
    int single_quotes;
    int double_quotes;

    single_quotes = 0;
    double_quotes = 0;
	if(check_pipe(ptr))
	{
		bash->exit_status = 1;
		return (1);
	}
	if(check_quotes_errors(ptr , &single_quotes , &double_quotes))
	{
		if(single_quotes == 1)
			ft_putstr_fd("'\n",2);
		else
			ft_putstr_fd("\"\n",2);
		bash->exit_status = 1;
		return (bash->exit_status);
	}
	remove_unprint(ptr);
	if (handel_redirection(bash , ptr))
		return (1);
	if (handle_pipe(bash, ptr))
		return (1);
    return (0);
}
