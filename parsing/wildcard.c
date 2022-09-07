/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:14:29 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/05 18:29:15 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_is_wildcard(t_list **arg, int i)
{
	int				yes;
	DIR				*dir;
	struct dirent	*dirent;

	yes = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	dirent = readdir(dir);
	while (dirent)
	{
		if (dirent->d_name[0] != '.' && ++yes)
		{
			ft_lstinsert(arg, ft_lstnew(ft_strdup(dirent->d_name), 0));
			(*arg) = (*arg)->next;
		}
		dirent = readdir(dir);
		if (dirent && dirent->d_name[0] != '.' && yes && i == 1)
		{
			ft_lstinsert(arg, ft_lstnew(ft_strdup(" "), 0));
			(*arg) = (*arg)->next;
		}
	}
	closedir(dir);
	return (yes);
}

static void	del_stars(t_list **arg)
{
	t_list	*tmp;

	if (ft_strcmp((*arg)->content, "*") == 0 && (*arg)->quoted == 0)
	{
		tmp = (*arg);
		(*arg) = (*arg)->next;
		ft_lstdelone(tmp, free);
	}
	tmp = (*arg);
	while (tmp)
	{
		if (tmp->next && ft_strcmp(tmp->next->content, "*") == 0
			&& tmp->next->quoted == 0)
		{
			ft_dellst(&tmp, tmp->next);
		}
		tmp = tmp->next;
	}
}

void	ft_wildcard(t_list **arg)
{
	int		i;
	int		check;
	t_list	*tmp;

	i = 0;
	tmp = (*arg);
	if (ft_cmpecho(tmp->content) == 0)
		i = 1;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, "|") == 0 && tmp->quoted == 0)
		{
			tmp = tmp->next;
			if (ft_cmpecho(tmp->content) == 0)
				i = 1;
			else
				i = 0;
		}
		if (ft_strcmp(tmp->content, "*") == 0
			&& tmp->quoted == 0)
			check = ft_is_wildcard(&tmp, i);
		tmp = tmp->next;
	}
	if (check)
		del_stars(arg);
}
