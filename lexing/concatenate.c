/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:09:53 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/07/06 23:20:43 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	not_space(t_list *arg)
{
	if ((ft_strcmp(arg->content, " ") && ft_is_opp(arg) == 0)
		|| (ft_strcmp(arg->content, " ") == 0 && arg->quoted))
		return (1);
	return (0);
}

static int	not_opp(t_list *arg)
{
	if (ft_is_opp(arg) && arg->quoted)
		return (1);
	return (0);
}

void	concatenate(t_list *arg)
{
	char	*tmp;

	while (arg)
	{
		if (arg->next && ((not_space(arg) && not_space(arg->next))
				|| not_opp(arg) || not_opp(arg->next))
			&& (arg->quoted != 4 && arg->next->quoted != 4))
		{
			tmp = arg->content;
			arg->content = ft_strjoin(arg->content, arg->next->content);
			arg->quoted = 3;
			free(tmp);
			ft_dellst(&arg, arg->next);
		}
		else
			arg = arg->next;
	}
}
