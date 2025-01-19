#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "./libft/libft.h"

//structure for environment variables
typedef struct  s_env{
    char * name ;
    char *value;
    struct s_env *next;
} t_env ;
//structure for redirections
typedef struct s_red
{
	char				*value;
	int 				type;
	struct s_red		*next;
}t_red;
//structure for commands
typedef struct s_cmd
{
    char *cmd;
    char **args;
    t_red *in;
    t_red *out;
    struct s_cmd *next;
} t_cmd;
//structure for bash
typedef struct s_bash
{
	t_env	*env;
	t_cmd	*cmd;
	int		exit_status;
}t_bash;





//handle_quotes.c
int     check_quotes_errors(char *input, int *single_quotes, int *double_quotes);
void	truck(char *input);
void	remove_unprint(char *ptr);
int check_pipe(char *ptr);
int		handle_quotes(t_bash *bash, char *ptr);

//redirection.c
int skip_red(char *ptr, int *qoutes);
int error_red(char *ptr);
int handle_pipe(t_bash *bash, char *ptr);
void check_qoutes(char input, int *qoutes);
int handel_redirection(t_bash *bash, char *ptr);

//read_line.c
//read line from user
void	inpute(t_bash *bash);
void handle_error(char *data,char *message);

//parcing_herdoc.c
int  help_red(char ptr , int *flag);
int size_rd(char *ptr, char *dst);
t_red *save_rd(char *ptr);

//parcing_redirection.c
void set_typ(char **ptr, int *type);
int get_value(t_env *env, char *value);
int get_value(t_env *env, char *value);
t_red *save_redirection(char *ptr, t_env *env);


//environment.c	//done
void    free_env(t_env * env);
t_env	*get_env(char *env);
void    env_add_back(t_env **head, t_env * curent);
t_env   *cnv_env(char **env);
t_bash  *allocation(char **env);













#endif