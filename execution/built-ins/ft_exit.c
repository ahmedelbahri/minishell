/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:54:50 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/02 04:23:28 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	exit_with_arg(char **content)
{
	int	i;

	i = 0;
	while (i < (int)strlen(content[1]))
	{
		if (ft_isalpha(content[1][i]))
		{
			printf("Error:\n exit: %s: numeric argument required\n"
				, content[1]);
			break ;
		}
		i++;
	}
	return (ft_atoi(content[1]));
}

int	ft_exit(char **content, t_env *env)
{
	int	res;

	res = 0;
	printf("exit\n");
	if (ft_dubstrlen(content) > 2)
	{
		ft_error("Error:\n exit: too many arguments\n");
		return (1);
	}
	ft_free_env(env);
	if (ft_dubstrlen(content) == 2)
		exit(exit_with_arg(content));
	exit(1);
	return (0);
}