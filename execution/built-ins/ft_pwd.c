/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 04:19:30 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/02 04:30:18 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(char **content, t_env *env)
{
	if (ft_dubstrlen(content) >= 2)
	{
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