/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_between_include.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:16:43 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/07/04 13:48:08 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmpecho(const char *s)
{
	size_t	i;
	char	*echo;

	i = 0;
	echo = "echo";
	while (s[i] && echo[i]
		&& ((echo[i] == s[i])
			|| (s[i] <= 90 && s[i] >= 65 && (echo[i] - 32) == s[i])))
		i++;
	return (s[i] - echo[i]);
}

void	del_in_between(t_list **tmp)
{
	while ((*tmp))
	{
		if (ft_strcmp((*tmp)->content, "|") == 0)
		{
			(*tmp) = (*tmp)->next;
			break ;
		}
		if ((*tmp)->next && ft_strcmp((*tmp)->next->content, " ") == 0)
			ft_dellst(tmp, (*tmp)->next);
		(*tmp) = (*tmp)->next;
	}
}

void	is_echo(t_list **tmp)
{
	while (*tmp)
	{
		if (ft_strcmp((*tmp)->content, "|") == 0)
		{
			(*tmp) = (*tmp)->next;
			break ;
		}
		else if (ft_cmpecho((*tmp)->content) == 0 && (*tmp)->next
			&& ft_strcmp((*tmp)->next->content, " ") == 0)
		{
			ft_dellst(tmp, (*tmp)->next);
			if ((*tmp)->next && ft_strcmp((*tmp)->next->content, "-n") == 0)
			{
				(*tmp) = (*tmp)->next;
				if ((*tmp)->next && ft_strcmp((*tmp)->next->content, " ") == 0)
					ft_dellst(tmp, (*tmp)->next);
			}
		}
		(*tmp) = (*tmp)->next;
	}
}