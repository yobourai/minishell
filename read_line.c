/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:19:47 by yobourai          #+#    #+#             */
/*   Updated: 2025/01/26 23:52:48 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *data, char *message)
{
	if (data)
		free(data);
	ft_putstr_fd(message, 2);
}

void	inpute(t_bash *bash)
{
	char	*str;
	int		exit_status;

	while (1)
	{
		str = readline("minishell : ");
		if (!str)
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
			bash->cmd = (t_cmd *)malloc(sizeof(t_cmd));
			if (!bash->cmd)
			{
				free_env(bash->env);
				exit_status = bash->exit_status;
				free(bash);
				exit(exit_status);
			}
			if (redirection(bash, str))
				break ;
			free(bash->cmd);
			bash->cmd = NULL;
		}
		free(str);
	}
}
