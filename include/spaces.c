/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:18:53 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/22 15:11:33 by ahel-bah         ###   ########.fr       */
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

void	del_spaces(t_list **arg)
{
	if (((*arg)->next && (*arg)->next->quoted == 0
			&& ft_strcmp((*arg)->next->content, " ") == 0))
		ft_dellst(arg, (*arg)->next);
	// if (ft_strcmp(ft_lstbeforelast(*arg)->content, " ") == 0)
}
