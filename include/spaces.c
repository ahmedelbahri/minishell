/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:18:53 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/24 11:38:30 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstbeforelast(t_list *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next && lst->next->next)
		lst = lst->next;
	return (lst);
}

int	only_space(t_list *arg)
{
	if (ft_lstsize(arg) == 1 && arg->quoted == 0
		&& ft_strcmp(arg->content, " ") == 0)
		return (1);
	return (0);
}

// static int	donotdelete(t_list *arg)
// {
// 	int	i;

// 	while (arg)
// 	{
// 		if ((arg->content, "echo"))
// 			;
// 		arg = arg->next;
// 	}
// }

// static void	in_between(t_list **arg)
// {
// 	donotdelete();
// }

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
	if ((*arg)->next && (*arg)->next->quoted == 0
		&& ft_strcmp((*arg)->next->content, " ") == 0)
		ft_dellst(arg, (*arg)->next);
	if (ft_lstbeforelast(*arg)->next != NULL
		&& ft_strcmp(ft_lstbeforelast(*arg)->next->content, " ") == 0)
	{
		tmp = ft_lstbeforelast(*arg);
		ft_dellst(&tmp, ft_lstlast(*arg));
	}
	// in_between(arg);
}
