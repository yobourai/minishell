/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:17:58 by yobourai          #+#    #+#             */
/*   Updated: 2025/01/26 23:43:53 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_bash	*bash;

	(void)ac;
	(void)av;
	bash = allocation(env);
	while (1)
	{
		inpute(bash);
		printf("command ready for excution\n");
	}
	return (0);
}
