/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:08:59 by waelhamd          #+#    #+#             */
/*   Updated: 2022/09/08 17:34:41 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//abort if old pwd not found
//cd path fin ghadi nmchi + t9der tkon chdir( . , .. , / )  wla - wla
char *ft_getenv(t_env *envirement, char *name)
{
	t_env *env;
	
	env = envirement;
	while(env)
	{
		if(!ft_strcmp(name, env->name))
			 return (env->content);
		env = env->next;
	}
	return (NULL);
}

static int argument_dir(char *path, t_env *env)
{
	char *str;
	int i;

	if(!ft_strncmp(path, "-", 1))
	{
		str = ft_getenv(env, "OLDPWD");
		if(!str)
			printf("cd: OLDPWD not set\n");
		i = chdir(str);
		printf("%s\n", str);
		 free(str);
		return(i);
	}
	else
		return(chdir(path));
	return (-1);
}


char	*get_pwd_env(t_env *list)
{
	t_env	*tmp;
	char		*pwd;

	tmp = list;
	pwd = NULL;
	while (tmp)
	{
		if (!ft_strcmp (tmp->name, "PWD"))
			pwd = ft_strdup (tmp->content);
		tmp = tmp->next;
	}
	return (pwd);
}

int	update_pwd_env(t_env **env)
{
	char		*current;
	char		*old;
	t_env	*tmp;

	tmp = *env;
	current = getcwd (NULL, 0);
	if (!current)
		return (-1);
	old = get_pwd_env (*env);
	while (tmp)
	{
		if (!ft_strcmp (tmp->name, "PWD"))
			tmp->content = current;
		else if (!ft_strcmp (tmp->name, "OLDPWD"))
			tmp->content = old;
		tmp = tmp->next;
	}
	return (0);
}

void	ft_cd(char **cmd, t_env *env)
{
	int i;
	char *path;

	if (!cmd[1] || !ft_strncmp(cmd[1], "~",1))
	{
		path = ft_getenv(env, "HOME");
		if(!path)
		{
			 g_exit_status = 1;
			printf("cd: HOME not set\n");
		}
		i = chdir(path);
		// free(path); 
	}
	else
		i = argument_dir(cmd[1], env);
	if(i < 0)
	{
		 g_exit_status = 1;
		perror("cd");
	}
	update_pwd_env(&env);
}