/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:29:38 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/02 04:20:24 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	cd_cmd(char **cmd, char **env)
// {

// }

// void	export_cmd(char **cmd, char **env)
// {

// }

// void	pwd_cmd(char **cmd, char **env)
// {

// }

// void	unset_cmd(char **cmd, char **env)
// {

// }

//nchofo ila kanet builtins wla la
// static bool	is_built_in(char *cmd)
// {
// 	if (!cmd)
// 		return (false);
// 	if (ft_strncmp(cmd, "cd", 3))
// 		return (true);
// 	else if (ft_strncmp(cmd, "pwd", 4))
// 		return (true);
// 	else if (ft_strncmp(cmd, "echo", 5))
// 		return (true);
// 	else if (ft_strncmp(cmd, "env", 4))
// 		return (true);
// 	else if (ft_strncmp(cmd, "export", 7))
// 		return (true);
// 	else if (ft_strncmp(cmd, "unset", 6))
// 		return (true);
// 	else if (ft_strncmp(cmd, "exit", 6))
// 		return (true);
// 	return (false);
// }

// ila kanet builtin n executiwha
int	exec_built_in(char **content, t_env *env)
{
	if (ft_strcmp(content[0], "exit") == 0)
		return (ft_exit(content, env));
	else if (ft_strcmp(content[0], "env") == 0)
		return (ft_env_cmd(env, content));
	else if (ft_strcmp(content[0], "echo") == 0)
		return (ft_echo(content));
	else if (ft_strcmp(content[0], "pwd") == 0)
		return (ft_pwd(content, env));
	// else if (ft_strncmp(cmd[0], "cd", 3))
	// 	return (cd_cmd(cmd));
	// else if (ft_strncmp(cmd[0], "export", 7))
	// 	return (export_cmd(cmd));
	// else if (ft_strncmp(cmd[0], "unset", 6))
	// 	return (unset_cmd(cmd));
	return (0);
}

// ila l9it l binaire return 0 true  sinon 1 false
// char	*get_absolute_path(char **cmd, char **env)
// {
// 	char *path;
// 	char **split_path;
// 	char *join;
// 	int i = 0;
// 	path = getenv("PATH");
// 	split_path = ft_split(path, ':');
// 	while(split_path[i])
// 	{
// 		join = ft_strjoin(split_path[i], "/");
// 		path = ft_strjoin(join, cmd);
// 		free(join);
// 		if(access(path, F_OK) == 0)
// 		{
// 			//free split_path defenitly
// 			return(path);
// 		}
// 		i++;
// 	}
// 	//free split_path (possible lost)
// 	return (NULL);
// }

// void	execution(char **cmd, char **env)
// {

// 	if (is_built_in(cmd[0]) == true) 
// 		exec_built_in(cmd);
// 	else if ((cmd[0] = get_absolute_path(cmd, env)) != NULL)
// 		exec_cmd(cmd, env);
// }

void	ft_execute(t_cmd *cmd, t_env *env)
{
	int	exit_status;

	exit_status = 0;
	while (cmd)
	{
		exit_status = exec_built_in(cmd->content, env);
		cmd = cmd->next;
	}
}
