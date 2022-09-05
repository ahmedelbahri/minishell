/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:08:59 by waelhamd          #+#    #+#             */
/*   Updated: 2022/09/05 20:03:03 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//cd path fin ghadi nmchi + t9der tkon chdir( . , .. , / )  wla - wla ~
static int argument_dir(char *path)
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

void	ft_cd(char **cmd)
{
	int i;
	char *path;

	if (!cmd[1] || !ft_strncmp(cmd[1], "~",1))
	{
		path = getenv("HOME");
		if(!path)
		{
			 g_exit_status = 1;//********************************
			printf("cd: HOME not set\n");
		}
		i = chdir(path);
		// free(path); 
	}
	else
		i = argument_dir(cmd[1]);
	if(i < 0)
	{
		 g_exit_status = 1;//*****************************************
		perror("cd");
	}
}