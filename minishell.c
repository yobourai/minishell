
#include "minishell.h"

int main(int ac, char **av, char **env)
{
    t_bash *bash;

    (void)ac;
    (void)av;
    bash = allocation(env);
    while (1)
    {
        inpute(bash);
        printf("command ready for excution\n");
    }
    return 0;
}