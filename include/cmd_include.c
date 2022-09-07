/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_include.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:02:03 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/07 04:14:57 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_cmdnew(char **content, int *quoted, int *pipe)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == 0)
		return (0);
	cmd->content = content;
	cmd->quoted = quoted;
	cmd->pipe = pipe;
	cmd->red = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*ft_cmdlast(t_cmd *cmd)
{
	if (cmd == NULL)
		return (0);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	ft_cmddelone(t_cmd *cmd, void (*del)(void*))
{
	free_dub(cmd->content);
	ft_redclear(&(cmd->red), del);
	del(cmd->quoted);
	del(cmd->pipe);
	free(cmd);
}

void	ft_cmdclear(t_cmd **cmd, void (*del)(void*))
{
	t_cmd	*tmp;

	tmp = NULL;
	while (*cmd != NULL)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		ft_cmddelone(tmp, del);
	}
	*cmd = NULL;
}

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*cmd1;

	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	cmd1 = ft_cmdlast(*cmd);
	cmd1->next = new;
}
