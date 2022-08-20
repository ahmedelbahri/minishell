/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:18:53 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/08/20 04:53:37 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_space(t_list *arg)
{
	if (ft_lstsize(arg) == 1 && arg->quoted == 0
		&& ft_strcmp(arg->content, " ") == 0)
		return (1);
	return (0);
}

static t_list	*ft_lstbeforelast(t_list *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next && lst->next->next)
		lst = lst->next;
	return (lst);
}

static void	in_between(t_list **arg)
{
	t_list	*tmp;

	tmp = (*arg);
	while (tmp)
	{
		if (tmp->next && ft_cmpecho(tmp->content))
			del_in_between(&tmp);
		else
			is_echo(&tmp);
	}
}

void	del_spaces(t_list **arg)
{
	t_list	*tmp;

	if (ft_lstsize(*arg) > 1
		&& ft_strcmp((*arg)->content, " ") == 0 && (*arg)->quoted == 0)
	{
		tmp = (*arg);
		(*arg) = (*arg)->next;
		ft_lstdelone(tmp, free);
	}
	if (ft_lstbeforelast(*arg)->next != NULL
		&& ft_strcmp(ft_lstbeforelast(*arg)->next->content, " ") == 0)
	{
		tmp = ft_lstbeforelast(*arg);
		ft_dellst(&tmp, ft_lstlast(*arg));
	}
	in_between(arg);
}
