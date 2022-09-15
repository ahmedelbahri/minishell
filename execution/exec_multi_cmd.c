/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:29:38 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/10 23:31:44 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_return(char *s1, char *s2)
{
	if ((s1 && s2) || s2)
		return (s2);
	else if (s1)
		return (s1);
	return (NULL);
}

char	*get_absolute_path(char *cmd, t_env *env, char *s1, char *s2)
{
	char	*path;
	char	**split_path;
	char	*join;
	int		i;

	i = -1;
	if (access(cmd, (F_OK | X_OK)) == 0)
			s1 = cmd;
	split_path = ft_split(ft_getenv(env, "SPATH"), ':');
	if (!split_path)
		return (NULL);
	while (split_path[++i] != NULL && *split_path)
	{
		join = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(join, cmd);
		free(join);
		if (access(path, X_OK) == 0)
				s2 = path;
		else
			free(path);
	}
	free_dub(split_path);
	return (ft_return(s1, s2));
}

static void	execute(t_cmd *cmd, t_env **env, int fd[])
{
	char	**cmd_tab;
	char	*str;
	char	**enironment;
	t_env	*tmp;

	signal(SIGINT, cmd_handler);
	tmp = (*env);
	cmd_tab = cmd->content;
	enironment = lst_to_array(tmp, NULL);
	if (cmd->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
	}
	if (exec_builtins(cmd_tab, cmd->red, *env) || !check_redirections(cmd->red))
		exit(g_exit_status);
	if (!cmd_tab || !cmd_tab[0])
		exit(0);
	str = cmd_tab[0];
	cmd_tab[0] = get_absolute_path(str, *env, NULL, NULL);
	if (execve(cmd_tab[0], cmd_tab, enironment) < 0)
		(printf("minishell: %s: command not found\n", str), exit(127));
}

void	exec_multi_cmd(t_cmd *cmd_list, t_env **env)
{
	int	fd[2];
	int	pid;

	while (cmd_list)
	{
		if (cmd_list->next)
			pipe(fd);
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid < 0)
			return (perror("fork"));
		if (pid == 0)
		{
			execute(cmd_list, env, fd);
		}
		if (cmd_list->next)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
		else
			close(0);
		cmd_list = cmd_list->next;
	}
}

void	exec_all(t_cmd *cmd, t_env **env)
{
	int	status;
	int	save_fd;
	int	flag;

	status = 0;
	save_fd = dup(0);
	if (cmd && !cmd->next && exec_builtins(cmd->content, cmd->red, *env))
	{
		g_exit_status = 0;
		return ;
	}
	exec_multi_cmd(cmd, env);
	flag = 0;
	while (flag != -1)
	{
		flag = waitpid (-1, &status, 0);
		if (WIFSIGNALED(status) && flag != -1)
		{
			if (WTERMSIG(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		else if (WIFEXITED(status) && flag != -1)
			g_exit_status = WEXITSTATUS (status);
	}
	dup2(save_fd, 0);
}
