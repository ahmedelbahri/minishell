/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 04:19:30 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/06 15:38:17 by waelhamd         ###   ########.fr       */
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
// void	pwd_cmd(char **cmd)
// {
// 	char	str[1024];

// 	if (!cmd || !*cmd || ft_strncmp(cmd[0], "pwd", 255))
// 		return ;
// 	if (getcwd(str, 1024))
// 	{
// 		ft_putstr_fd(str, 1);
// 		ft_putstr_fd("\n", 1);
// 	}
// 	else
// 		perror("pwd:");
// }