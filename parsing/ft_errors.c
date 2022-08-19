/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:29:38 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/08/19 22:04:56 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	invalid_dollar(t_list *arg)
{
	if (ft_lstsize(arg) == 1 && arg->quoted == 4)
		return (1);
	return (0);
}

int	ft_is_red(t_list *arg)
{
	if (ft_strcmp(arg->content, "<<") == 0
		|| ft_strcmp(arg->content, ">>") == 0
		|| ft_strcmp(arg->content, "<") == 0
		|| ft_strcmp(arg->content, ">") == 0)
		return (1);
	return (0);
}

static int	ft_dub_opp(t_list *arg)
{
	while (arg)
	{
		if ((ft_strcmp(arg->content, "|") == 0 && arg->quoted == 0 && arg->next
				&& ft_strcmp(arg->next->content, "|") == 0
				&& arg->next->quoted == 0)
			|| (ft_is_red(arg) && arg->quoted == 0 && arg->next
				&& ft_is_red(arg->next) && arg->next->quoted == 0)
			|| (ft_lstsize(arg) == 1 && ft_is_opp(arg) && arg->quoted == 0))
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
	if (invalid_dollar(arg) || ft_dub_opp(arg))
		return (1);
	return (0);
}
