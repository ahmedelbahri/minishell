/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:29:38 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/08/02 15:11:37 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute(t_cmd *cmd, t_env *env)
{
	env = NULL;
	if (ft_strcmp(cmd->content[0], "exit") == 0)
	{
		printf("exit\n");
		ft_free_env(env);
		exit(0);
	}
}