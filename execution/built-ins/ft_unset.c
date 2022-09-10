/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:30:38 by waelhamd          #+#    #+#             */
/*   Updated: 2022/09/10 23:52:00 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	validator(char *line)
{
	int	i;

	i = 0;
	if (!ft_isalpha(line[i]) && line[i] != '_')
	{
		g_exit_status = 1;
		return (printf("unset: '%s': not a valid identifier\n", line), 0);
	}
	while (line[i])
	{
		if (!ft_isalnum(line[i]) && line[i] != '_')
		{
			g_exit_status = 1;
			return (printf("unset: '%s': not a valid identifier\n", line), 0);
		}
		i++;
	}
	return (1);
}

static void	free_variable(t_env *save)
{
	free(save->name);
	free(save->content);
	free(save);
}

static void	del_variable(char *name, t_env *tmp_lst)
{
	t_env	*save;

	while (tmp_lst && tmp_lst->next)
	{
		if (!ft_strcmp(name, tmp_lst->next->name))
		{
			save = tmp_lst->next;
			if (tmp_lst->next->next == NULL)
				tmp_lst->next = NULL;
			else
				tmp_lst->next = tmp_lst->next->next;
			free_variable(save);
			break ;
		}
		tmp_lst = tmp_lst->next;
	}
}

void	ft_unset(char **cmd, t_env *env)
{
	int		i;
	t_env	*tmp_lst;

	i = 1;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "PATH"))
			del_variable("SPATH", env);
		if (!validator(cmd[i]))
			return ;
		tmp_lst = env;
		if (!ft_strcmp(cmd[i], tmp_lst->name))
		{
			env = env->next;
			free_variable(tmp_lst);
		}
		else
			del_variable(cmd[i], tmp_lst);
		i++;
	}
}
