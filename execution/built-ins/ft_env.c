/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:33:27 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/05 18:53:39 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		if (env->content)
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
		if(env->content)
		{
			printf("%s", env->name);
			printf("=");
			printf("%s\n", env->content);
		}
		env = env->next;
	}
}
// 7ayed return
int	ft_env_cmd(t_env *env, char **content)
{
	if (ft_dubstrlen(content) > 1)
	{
		printf("Error :\n env: invalid argument: %s\n", content[1]);
		g_exit_status = 0;
		return (0);
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
		if (ft_strcmp(ft_envlast(env)->name, "SHLVL") == 0
            && ft_envlast(env)->content[0] - 48 < 9)
            ft_envlast(env)->content[0]++;
		i++;
	}
	return (env);
}
