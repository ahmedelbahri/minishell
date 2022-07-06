/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:29:38 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/07/06 23:22:42 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	del_invalid_dollar(t_list *arg)
{
	while (arg)
	{
		if (arg->next && arg->next->quoted == 4)
			ft_dellst(&arg, arg->next);
		if (ft_lstsize(arg) == 1 && arg->quoted == 4)
			return (1);
		arg = arg->next;
	}
	return (0);
}
static int	ft_dub_opp(t_list *arg)
{
	while (arg)
	{
		if ((ft_is_opp(arg) == 0 && arg->next && ft_is_opp(arg->next) == 0)
			|| (ft_lstsize(arg) == 1 && ft_is_opp(arg)))
		{
			perror("error");
			return (1);
		}
		arg = arg->next;
	}
	return (0);
}


int	ft_errors(t_list *arg)
{
	if (del_invalid_dollar(arg) || ft_dub_opp(arg))
		return (1);
	return (0);
}
