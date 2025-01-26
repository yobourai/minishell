/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:19:47 by yobourai          #+#    #+#             */
/*   Updated: 2025/01/26 05:19:48 by yobourai         ###   ########.fr       */
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
			printf("parcing good \n%s\n", str);
		}
		free(str);
	}
}
