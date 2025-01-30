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

t_cmd	 *alloc_command()
{
	t_cmd *cmd;
	cmd =	(t_cmd *)malloc(sizeof(t_cmd));
		if (!cmd)
			return NULL;
		
		cmd->args = NULL;
		cmd->in = NULL;
		cmd->out = NULL;
		cmd->next = NULL;
	return cmd;
}
void	free_arry(char **ptr)
{
	int	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			free(ptr[i]);
			i++;
		}
		free(ptr);
	}
}
void	free_files(t_red *file)
{
	t_red	*current;

	while (file)
	{
		current = file->next;
		free(file->value);
		free(file);
		file = current;
	}
	
}

void free_cmd(t_cmd *cmd)
{
	t_cmd	*curent;

	while (cmd)
	{
		curent = cmd->next;
		free_arry(cmd->args);
		free_files(cmd->in);
		free_files(cmd->out);
		free(cmd);
		cmd = curent;
	}
}

void free_all(t_bash *bash)
{

	free_env(bash->env);
	free_cmd(bash->cmd);
	free(bash);
}

void	handle_error(char *data, char *message)
{
	if (data)
		free(data);
	ft_putstr_fd(message, 2);
}

void	inpute(t_bash *bash)
{
	char	*str;

	while (1)
	{
		str = readline("minishell : ");
		if (!str)
		{
			free_all(bash);
			exit(7);
		}
		add_history(str);
		if (handle_quotes(bash, str) == 0)
		{
			bash->cmd = alloc_command();
			if(!bash->cmd)
			{
				free(str);
				free_all(bash);
				exit(7);
			}
			if (!get_command_info(bash, str))
			{
				free(str);
				break ;
			}
			free_cmd(bash->cmd);
			bash->cmd = NULL;
		}
		free(str);
	}
}
