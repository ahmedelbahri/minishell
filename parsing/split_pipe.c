/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:12:45 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/07/21 20:22:28 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_dub(char **content)
{
	int	i;
	int	len;

	i = 0;
	len = ft_dubstrlen(content);
	while (i < len)
	{
		free(content[i]);
		i++;
	}
	free(content);
}

static char	**reallocate_cmd(char **content, char *arg_content)
{
	char	**new_content;
	int		content_len;
	int		i;

	if (content == NULL)
	{
		new_content = malloc(sizeof(char *) * 2);
		new_content[0] = ft_strdup(arg_content);
		new_content[1] = NULL;
	}
	else
	{
		content_len = ft_dubstrlen(content);
		new_content = malloc(sizeof(char *) * (content_len + 2));
		i = 0;
		while (i < content_len)
		{
			new_content[i] = ft_strdup(content[i]);
			i++;
		}
		new_content[i++] = ft_strdup(arg_content);
		new_content[i] = NULL;
		free_dub(content);
	}
	return (new_content);
}

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

	content = NULL;
	quoted = NULL;
	while (*arg)
	{
		if (ft_strcmp((*arg)->content, "|"))
		{
			content = reallocate_cmd(content, (*arg)->content);
			quoted = quots(quoted, (*arg)->quoted, ft_dubstrlen(content));
		}
		else
			break ;
		(*arg) = (*arg)->next;
	}
	ft_cmdadd_back(cmd, ft_cmdnew(content, quoted));
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
