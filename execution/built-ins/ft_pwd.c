/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 04:19:30 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/10 23:50:11 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(char **content, t_env *envp)
{
	t_env	*env;
	char	*pwd;

	env = envp;
	pwd = NULL;
	if (ft_dubstrlen(content) >= 2)
	{
		g_exit_status = 1;
		ft_error("Error:\n pwd: too many arguments\n");
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = ft_getenv(env, "PWD");
		printf("%s\n", pwd);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	return (0);
}
