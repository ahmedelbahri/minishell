/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:29:38 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/07/19 18:43:19 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	del_invalid_dollar(t_list **arg)
{
	t_list	*tmp;

	if ((*arg)->quoted == 4 && (*arg)->next)
	{
		tmp = (*arg);
		(*arg) = (*arg)->next;
		ft_lstdelone(tmp, free);
	}
	tmp = (*arg);
	while (tmp)
	{
		if (tmp->next && tmp->next->quoted == 4)
			ft_dellst(&tmp, tmp->next);
		if (ft_lstsize(tmp) == 1 && tmp->quoted == 4)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	ft_dub_opp(t_list *arg)
{
	while (arg)
	{
		if ((ft_is_opp(arg) && arg->next && ft_is_opp(arg->next))
			|| (ft_lstsize(arg) == 1 && ft_is_opp(arg)))
		{
			perror("error");
			return (1);
		}
		arg = arg->next;
	}
	return (0);
}

int	ft_errors(t_list **arg)
{
	if (del_invalid_dollar(arg) || ft_dub_opp(*arg))
		return (1);
	return (0);
}
