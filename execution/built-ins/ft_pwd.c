/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 04:19:30 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/04 15:45:07 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(char **content, t_env *envp)
{
	t_env *env;

	env = envp;
	if (ft_dubstrlen(content) >= 2)
	{
		g_exit_status = 1;
		ft_error("Error:\n pwd: too many arguments\n");
		return (1);
	}
	while (env)
	{
		if (ft_strcmp(env->name, "PWD") == 0)
		{
			printf("%s\n", env->content);
			break ;
		}
		env = env->next;
	}
	return (0);
}