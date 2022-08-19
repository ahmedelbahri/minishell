/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:33:27 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/08/01 19:19:41 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		ft_envadd_back(&env, ft_envnew(ft_substr(nv[i], start,
					ft_strlen(nv[i])), ft_substr(nv[i], 0, start - 1)));
		i++;
	}
	return (env);
}
