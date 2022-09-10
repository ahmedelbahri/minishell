/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:17:37 by waelhamd          #+#    #+#             */
/*   Updated: 2022/09/10 23:23:30 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtins(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp(cmd, "cd", 3))
		return (true);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (true);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (true);
	else if (!ft_strncmp(cmd, "env", 4))
		return (true);
	else if (!ft_strncmp(cmd, "export", 7))
		return (true);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (true);
	else if (!ft_strncmp(cmd, "exit", 6))
		return (true);
	return (false);
}

int	exec_builtins(char **cmd, t_red *red, t_env *env)
{
	int	fd[2];

	if (!cmd[0] || is_builtins(cmd[0]) == false)
		return (0);
	fd[0] = dup(0);
	fd[1] = dup(1);
	if (check_redirections(red))
	{
		if (!ft_strncmp(cmd[0], "cd", 3))
			ft_cd(cmd, env);
		else if (!ft_strncmp(cmd[0], "pwd", 4))
			ft_pwd(cmd, env);
		else if (!ft_strncmp(cmd[0], "echo", 5))
			ft_echo(cmd);
		else if (!ft_strncmp(cmd[0], "env", 4))
			ft_env_cmd(env, cmd);
		else if (!ft_strncmp(cmd[0], "export", 7))
			ft_export(cmd, &env);
		else if (!ft_strncmp(cmd[0], "unset", 6))
			ft_unset(cmd, env);
		else if (!ft_strncmp(cmd[0], "exit", 6))
			ft_exit(cmd, env);
	}
	return (dup2(fd[0], 0), dup2(fd[1], 1), close(fd[0]), close(fd[1]), 1);
}
