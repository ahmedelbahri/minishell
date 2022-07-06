/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:47:04 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/07/05 18:14:24 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		free(tmp->content);
		free(tmp->name);
		tmp = tmp->next;
	}
	free(env);
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
