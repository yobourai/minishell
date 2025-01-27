/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:18:13 by yobourai          #+#    #+#             */
/*   Updated: 2025/01/27 00:12:54 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// structure for environment variables
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;
// structure for redirections
typedef struct s_red
{
	char			*value;
	int				type;
	struct s_red	*next;
}					t_red;
// structure for commands
typedef struct s_cmd
{
	char			**args;
	t_red			*in;
	t_red			*out;
	struct s_cmd	*next;
}					t_cmd;
// structure for bash
typedef struct s_bash
{
	t_env			*env;
	t_cmd			*cmd;
	int				exit_status;
}					t_bash;

// handle_quotes.c
int					check_quotes_errors(char *input, int *single_quotes,
						int *double_quotes);
void				truck(char *input);
void				remove_unprint(char *ptr);
int					check_pipe(char *ptr);
int					handle_quotes(t_bash *bash, char *ptr);

// redirection.c
int					skip_red(char *ptr, int *qoutes);
int					error_red(char *ptr);
int					handle_pipe(t_bash *bash, char *ptr);
void				check_qoutes(char input, int *qoutes);
int					handel_redirection(t_bash *bash, char *ptr);

// read_line.c
// read line from user
void				inpute(t_bash *bash);
void				handle_error(char *data, char *message);

// parcing_herdoc.c
int					help_red(char ptr, int *flag);
int					size_rd(char *ptr, char *dst);
t_red				*save_rd(char *ptr);

//  redirection_utils.c
// typ of redirection
void				set_typ(char **ptr, int *type);
// valid or not valid char for expanding
int					is_valid_char(char c);
int					is_valid_char_first(char c);
int					is_valid_char1(char c);
// checking quotes
int					help_red_add(char ptr, int *flag);

// skipp space
void				skipp_space(char **ptr);

// redirecting_utils_ambg.c
// checking ambgous error
int					condition(char **ptr, int *flag);
int					handle_ambg(char *ptr);
int					cpy_ambg_size(char *ptr);
char				*cpy_ambg(char *ptr);

// redirection_utils2.c
// size
int					size_st(char *ptr, t_env *env);
int					size_hp(char **ptr, t_env *env);
// cpy value from env
char				*cpy_hp(char **ptr, t_env *env);
void				copy_value_hp(char **str, char *dest, int *flag,
						t_env *env);
char				*cpy_value(char **ptr, t_env *env, char *dest);

// parcing_redirection.c
// save redirection and checking all shit
t_red				*save_redirection_hp(char *ptr, t_env *env);
t_red	*save_redirection(char *ptr, t_env *env,int *flag);
int     redirection(t_bash *bash, char *src);
void    skip_at_end(char **ptr);

// environment.c	//done
void				free_env(t_env *env);
t_env				*get_env(char *env);
void				env_add_back(t_env **head, t_env *curent);
t_env				*cnv_env(char **env);
t_bash				*allocation(char **env);

#endif
