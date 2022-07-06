/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_include.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:02:03 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/07/05 15:30:37 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_cmdnew(char **content, int *quoted)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == 0)
		return (0);
	cmd->content = content;
	cmd->quoted = quoted;
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
	int	i;
	int	len;

	i = 0;
	len = ft_dubstrlen(cmd->content);
	while (i < len)
	{
		del(cmd->content[i]);
		i++;
	}
	del(cmd->content);
	del(cmd->quoted);
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
