/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:09:53 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/08/20 04:27:47 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	not_space(t_list *arg)
{
	if ((ft_strcmp(arg->content, " ")) || (ft_strcmp(arg->content, " ") == 0
			&& arg->quoted))
		return (1);
	return (0);
}

static int	not_opp(t_list *arg)
{
	if (ft_is_opp(arg) && arg->quoted == 0)
		return (1);
	return (0);
}

static void	del_invalid_dollar(t_list **arg)
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
			return ;
		tmp = tmp->next;
	}
}

void	concatenate(t_list **arg)
{
	char	*to_free;
	t_list	*tmp;

	del_invalid_dollar(arg);
	tmp = *arg;
	while (tmp)
	{
		if (tmp->next && ((not_space(tmp) && not_space(tmp->next))
				&& (not_opp(tmp) == 0 && not_opp(tmp->next) == 0))
			&& (tmp->quoted != 4 && tmp->next->quoted != 4))
		{
			to_free = tmp->content;
			tmp->content = ft_strjoin(tmp->content, tmp->next->content);
			tmp->quoted = 3;
			free(to_free);
			ft_dellst(&tmp, tmp->next);
		}
		else
			tmp = tmp->next;
	}
}
