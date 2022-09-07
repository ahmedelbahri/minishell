/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:12:45 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/07 04:06:27 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	*quots(int *cmdquoted, int quoted, int len)
{
	int			*new_quoted;
	int			i;

	if (cmdquoted == NULL)
	{
		new_quoted = malloc(sizeof(int) * 1);
		new_quoted[0] = quoted;
	}
	else
	{
		new_quoted = malloc(sizeof(int) * (len));
		i = 0;
		while (i < len - 1)
		{
			new_quoted[i] = cmdquoted[i];
			i++;
		}
		new_quoted[i] = quoted;
		free(cmdquoted);
	}
	return (new_quoted);
}

static void	ft_loop(t_list **arg, t_cmd **cmd)
{
	char	**content;
	int		*quoted;
	int		*pipe;

	content = NULL;
	pipe = NULL;
	quoted = NULL;
	while (*arg)
	{
		if (ft_strcmp((*arg)->content, "|")
			|| (ft_strcmp((*arg)->content, "|") == 0 && (*arg)->quoted))
		{
			content = reallocate_dub(content, (*arg)->content);
			quoted = quots(quoted, (*arg)->quoted, ft_dubstrlen(content));
			pipe = quots(pipe, (*arg)->pipe_0, ft_dubstrlen(content));
		}
		else
			break ;
		(*arg) = (*arg)->next;
	}
	ft_cmdadd_back(cmd, ft_cmdnew(content, quoted, pipe));
}

t_cmd	*split_pipe(t_list *arg)
{
	t_cmd	*cmd;

	cmd = NULL;
	while (arg)
	{
		if (ft_strcmp(arg->content, "|") || (ft_strcmp(arg->content, "|") == 0
				&& arg->quoted))
			ft_loop(&arg, &cmd);
		else if (ft_strcmp(arg->content, "|") == 0)
			arg = arg->next;
	}
	return (cmd);
}
