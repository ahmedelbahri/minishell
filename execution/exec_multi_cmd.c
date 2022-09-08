/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:29:38 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/08 17:15:37 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redirections(t_red *red);
static int	create_file(t_red *red, int fd);

char	*get_absolute_path(char *cmd, t_env *env)
{
	char *path;
	char **split_path;
	char *join;
	int i = 0;

	if(access(cmd, X_OK) == 0)
		return(cmd);
	path = ft_getenv(env, "PATH");
	split_path = ft_split(path, ':');
	while(split_path[i] != NULL)
	{
		join = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(join, cmd);
		free(join);
		if(access(path, X_OK) == 0)
		{
			//free split_path defenitly
			return(path);
		}
		i++;
	}
	//free split_path (possible lost)
	return (NULL);
}



static int	create_file(t_red *red, int fd)
{
	if (red->type == HERDOC)
	{
		// dup2(red->fd, 0);
		// close(red->fd);
		return (1);
	}
	if (red->type == INFILE)
	{
		fd = open(red->file_name, O_RDONLY);
		if (fd < 0)
			return (0);
		dup2(fd, 0);
		close(fd);
	}
	else
	{
		
		if (red->type == APPAND)
			fd = open(red->file_name, O_APPEND | O_CREAT | O_WRONLY, 0666);
		else
			fd = open(red->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			return (0);
		dup2(fd, 1);
		close(fd);
	}
	return (1);
}

// 1minishell:~$ < a
// minishell: (null): command not found
int	check_redirections(t_red *red)
{
	int	fd;

	fd = 0;
	while (red)
	{
		if (create_file(red, fd) == 0)
		{
			g_exit_status = 1;
			write(2, "minisehll: ", 11);
			perror(red->file_name);
			return (0);
		}
		red = red->next;
	}
	return (1);
}

static void	execute(t_cmd *cmd, t_env **env, int fd[])
{
	char	**cmd_tab;
	char	*str;
	char	**enironment;
	t_env *tmp;

	tmp = (*env);
	cmd_tab = cmd->content;
	enironment = lst_to_array(tmp);
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
	cmd_tab[0] = get_absolute_path(str, *env);
	execve(cmd_tab[0], cmd_tab, enironment);
	printf("minishell: %s: command not found\n", str);
	exit(1);
}

void	exec_multi_cmd(t_cmd *cmd_list, t_env **env)
{
	int	fd[2];
	int	pid;
	int save_fd;

	save_fd = dup(0);
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
			signal(SIGINT, cmd_handler);
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
	dup2(save_fd, 0);
}

void	exec_all(t_cmd *cmd, t_env **env)
{
	int status;
	int flag;

	status = 0;
	if(cmd && !cmd->next && exec_builtins(cmd->content, cmd->red, *env))
		return ;
	exec_multi_cmd(cmd, env);
	// signal(SIGINT, handler);
	flag = 0;
	while (flag != -1)
	{
		flag = waitpid (-1, &status, 0);
		if (WIFEXITED(status) && flag != -1)
			g_exit_status = WEXITSTATUS (status);
		else if (WIFSIGNALED (status) && flag != -1)
		{
			if (WTERMSIG(status) + 128 == 131)
			{
				g_exit_status = 131;
				printf ("Quit : 3\n");
			}
		}
	}	
}
/// wait ou handle exit satuts execution de builtins
