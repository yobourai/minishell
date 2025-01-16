#include "minishell.h"

void    inpute(t_bash *bash)
{
	char	*str;
	int exit_status;
    
    while (1)
	{
		str = readline("minishell : ");
		if(!str)
		{
			free_env(bash->env);
			exit_status = bash->exit_status;
			free(bash);
			printf("signle controle +D\n");
			exit(exit_status);
		}
		add_history(str);
		if (handle_quotes(bash, str) == 0)
		{

		// str = dollar_sign(str , env);
		// if(redairectionc_error(bash) == 1)
		// {
		// 	free(bash);
		// 	continue;
		// }
		// printf("%s\n",bash);
		// if (str == NULL)
		// {
		// 	printf("\nExiting...\n");
		// 	break;
		// }
			free(str);
		}
    }
}
