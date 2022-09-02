/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:33:27 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/02 04:44:12 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		free(env->content);
		free(env->name);
		env = env->next;
		free(tmp);
	}
}

void	print_env(t_env *env)
{
	while (env != NULL)
	{
		printf("%s", env->name);
		printf("=");
		printf("%s\n", env->content);
		env = env->next;
	}
}

int	ft_env_cmd(t_env *env, char **content)
{
	if (ft_dubstrlen(content) > 1)
	{
		printf("Error :\n env: invalid argument: %s\n", content[1]);
		return (127);
	}
	else
		print_env(env);
	return (0);
}

static int	ft_start(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i++] == '=')
			return (i);
	}
	return (0);
}

t_env	*ft_env(char **nv)
{
	int		i;
	int		start;
	t_env	*env;

	i = 0;
	env = NULL;
	while (nv[i])
	{
		start = ft_start(nv[i]);
		ft_envadd_back(&env, ft_envnew(ft_substr_lex(nv[i], start,
					ft_strlen(nv[i])), ft_substr_lex(nv[i], 0, start - 1)));
		i++;
	}
	return (env);
}
