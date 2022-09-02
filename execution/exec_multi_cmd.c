/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:29:38 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/02 04:50:41 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdbool.h>

int	handle_redirections(t_red *red);
static int	create_file(t_red *red, int fd);
//cd path fin ghadi nmchi + t9der tkon chdir( . , .. , / )  wla - wla ~
int argument_dir(char *path)
{
	char *str;
	int i;

	if(!ft_strncmp(path, "-", 1))
	{
		str = getenv("OLDPWD");
		if(!str)
			printf("cd: OLDPWD not set\n");
		i = chdir(str);
		printf("%s\n", str);
		// free(str);
		return(i);
	}
	else
		return(chdir(path));
	return (-1);
}

void	cd_built(char **cmd)
{
	int i;
	char *path;

	if (!cmd[1] || !ft_strncmp(cmd[1], "~",1))
	{
		path = getenv("HOME");
		if(!path)
		{
			// g_global.status = 1;********************************
			printf("cd: HOME not set\n");
		}
		i = chdir(path);
		// free(path);
	}
	else
		i = argument_dir(cmd[1]);
	if(i < 0)
	{
		// g_global.status = 1;*****************************************
		perror("cd");
	}
}

void	add_value(char *exp_arg, t_env *env)
{
	ft_envadd_back(&env, ft_envnew(exp_arg, NULL));
}

//ila kan ghadi nbdel lih content ila ma kanch ghadi ndir lih addback
void change_value(char **exp_arg, t_env *env)
{
	t_env	*head;
	size_t	i;
	int		check;

	check = 0;
	head = env;
	i = ft_strlen(exp_arg[0]);
	while(head)
	{
		if(ft_strncmp(exp_arg[0], head->name, i) == 0)
		{
			head->content = ft_strdup(exp_arg[1]);
			check = 1;
		}
		head = head->next;
	}
	head = env;
	if(check == 0)
		ft_envadd_back(&head, ft_envnew(exp_arg[1],exp_arg[0]));
}

void	export_built(char **cmd, t_env *env)
{
	char **exp_arg;

	if(!cmd[1])
		return(print_env(env));
		//khrej 9wed************************************
	exp_arg = ft_split(cmd[1], '=');
	if(!exp_arg[1])
		add_value(exp_arg[0],env);
	else
		change_value(exp_arg, env);
		
	// parsing export argument
	//cmd[1] = NULL printi env
}
//*******************************************************************************************
// void	pwd_built(char **cmd, char **env)
// {
	
// }

// void	unset_built(char **cmd, char **env)
// {
	
// }

// void	exit_built(char **cmd, char **env)
// {
	
// }
//*******************************************************************************************


//nchofo ila kanet builtins wla la
static bool	is_built_in(char *cmd)
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

// ila kanet builtin n executiwha
int	exec_built_in(char **cmd, t_red *red, t_env *env)
{
	int fd[2];

	if(!cmd[0] || !is_built_in(cmd[0]))
		return (0);
	fd[0] = dup(0);
	fd[1] = dup(1);
	if(handle_redirections(red))
	{
		if (ft_strncmp(cmd[0], "cd", 3))
			cd_built(cmd);
		// else if (ft_strncmp(cmd[0], "pwd", 4))
		// 	pwd_built();
		// else if (ft_strncmp(cmd[0], "echo", 5))
		// 	return (echo_built(cmd));
		else if (ft_strncmp(cmd[0], "env", 4))
			ft_env(cmd);
		else if (ft_strncmp(cmd[0], "export", 7))
			export_built(cmd, env);
		// else if (ft_strncmp(cmd[0], "unset", 6))
		// 	unset_built(cmd);
			// else if (ft_strncmp(cmd[0], "exit", 6))
		// 	exit_built(cmd);
	}
	return (dup2(fd[0], 0), dup2(fd[1], 1), close(fd[0]), close(fd[1]), 1);
}

// ila l9it l binaire return 0 true  sinon 1 false
char	*get_absolute_path(char *cmd)
{
	char *path;
	char **split_path;
	char *join;
	int i = 0;

	path = getenv("PATH");
	split_path = ft_split(path, ':');
	while(split_path[i] != NULL)
	{
		join = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(join, cmd);
		free(join);
		if(access(path, F_OK) == 0)
		{
			//free split_path defenitly
			return(path);
		}
		i++;
	}
	//free split_path (possible lost)
	return (NULL);
}

char	**lst_to_array(t_env *env)
{
	t_env	*tmp = env;
	char **array;
	size_t	i = 0;

	while (tmp) {
		i++;
		tmp= tmp->next;
	}
	array = (char **)malloc(sizeof(char *) * i + 1);
	if (!array)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp) 
	{
		array[i] = ft_strjoin(tmp->name, ft_strjoin("=", tmp->content));
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}


static int	create_file(t_red *red, int fd)
{
	// if (red->type == HERDOC)
	// {
	// 	dup2(red->fd, 0);
	// 	close(red->fd);
	// }
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

int	handle_redirections(t_red *red)
{
	int	fd;

	fd = 0;
	while (red)
	{
		if (create_file(red, fd) == 0)
		{
			//g_global.exit_status = 1;
			printf("minisehll: ");
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
	t_env *envp;

	envp = (*env);

	cmd_tab = cmd->content;
	enironment = lst_to_array(envp);
	if (cmd->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
	}
	// if (is_builtin_cmd(cmd_tab, cmd->red, env) || !handle_redirections(cmd->red))
		//exit(g_global.exit_status);
	// if (!cmd_lst || !cmd_lst[0])
	// 	exit(0);
	str = cmd_tab[0];
	cmd_tab[0] = get_absolute_path(str);
	if (!cmd_tab[0])
	{
		printf("minishell: %s: command not found\n", str);
		exit(1);
	}
	execve(cmd_tab[0], cmd_tab, enironment);
}

void	run_cmd(t_cmd *cmd, t_env **env, int fd[])
{
	execute(cmd, env, fd);
	if(!cmd->content[0])
		perror(cmd->content[0]);
	exit(1);
}

void	exec_multi_cmd(t_cmd *cmd_list, t_env **env)
{
	int	fd[2];
	int	pid;
	int tmp_fd;

	tmp_fd = dup(0);
	while (cmd_list)
	{
		if (cmd_list->next)
			pipe(fd);
		pid = fork();
		if (pid < 0)
			return (perror("fork"));
		if (pid == 0)
			run_cmd(cmd_list, env, fd);
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
	dup2(tmp_fd, 0);
}
