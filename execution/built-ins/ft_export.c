/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:13:07 by waelhamd          #+#    #+#             */
/*   Updated: 2022/09/10 23:49:28 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_envirenmet(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->name && ft_strcmp(tmp->name, "SPATH"))
		{
			printf("declare -x %s", tmp->name);
			if (tmp->content)
				printf("=\"%s\"", tmp->content);
			printf("\n");
		}
		tmp = tmp->next;
	}
}

static int	validator(char	*name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	while (name[i] != '=' && name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '+')
			return (0);
		if (name[i] == '+' && name[i + 1] == '=')
			return (i);
		i++;
	}
	return (i);
}

static int	add_or_change(char **tab, char s, t_env **envirenemt)
{
	t_env	*env;
	char	*save;

	env = *envirenemt;
	save = NULL;
	while (env)
	{
		if (!ft_strncmp(env->name, tab[0], ft_strlen(env->name)))
		{
			if (tab[1] || env->content)
			{
				save = env->content;
				if (s == '+' && save)
				{
					env->content = ft_strjoin(env->content, tab[1]);
					free(tab[1]);
				}
				else
					env->content = tab[1];
			}
			return (free(save), free(tab[0]), 0);
		}
		env = env->next;
	}
	return (ft_envadd_back(envirenemt, ft_envnew(tab[1], tab[0])), 0);
}

static int	export_element(char *name, t_env **env, int i)
{
	char	*tab[2];

	tab[0] = ft_substr(name, 0, i);
	if (name[i] == 0)
		tab[1] = NULL;
	else if (name[i] == '+')
		tab[1] = ft_substr(name, i + 2, ft_strlen(name) - i - 2);
	else
		tab[1] = ft_substr(name, i + 1, ft_strlen(name) - i - 1);
	if (ft_getenv((*env), tab[0]) && name[i] == '\0')
		return (free(tab[0]), free(tab[1]), 0);
	add_or_change(tab, name[i], env);
	if (!ft_strcmp(tab[0], "PATH") && tab[1])
	{
		tab[0] = ft_strdup("SPATH");
		if (ft_getenv((*env), "PATH"))
			tab[1] = ft_strdup(ft_getenv((*env), "PATH"));
		else
			tab[1] = NULL;
		add_or_change(tab, name[i], env);
	}
	return (0);
}

void	ft_export(char **cmd, t_env **env)
{
	int	i;
	int	val;

	i = 1;
	if (!cmd[1])
		return (print_envirenmet(*env));
	while (cmd[i])
	{
		val = validator(cmd[i]);
		if (val == 0)
		{
			g_exit_status = 1;
			printf("minishell: export: '%s': not a valid identifier\n", cmd[i]);
			return ;
		}
		export_element(cmd[i], env, val);
		i++;
	}
}
