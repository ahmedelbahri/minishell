/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:12:45 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/26 19:04:23 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_loop(t_list **arg, t_cmd **cmd)
{
	char	**content;

	content = NULL;
	while (*arg)
	{
		if (ft_strcmp((*arg)->content, "|"))
		{
			content = reallocate_cmd(content, (*arg)->content);
		}
		else
			break ;
		(*arg) = (*arg)->next;
	}
	ft_cmdadd_back(cmd, ft_cmdnew(content, 1));
}

t_cmd	*split_pipe(t_list *arg)
{
	t_cmd	*cmd;

	cmd = NULL;
	while (arg)
	{
		if (ft_strcmp(arg->content, "|"))
			ft_loop(&arg, &cmd);
		else if (ft_strcmp(arg->content, "|") == 0)
			arg = arg->next;
	}
	return (cmd);
}
