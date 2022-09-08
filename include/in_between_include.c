/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_between_include.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:16:43 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/08 17:59:41 by waelhamd         ###   ########.fr       */
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
		if (ft_strcmp((*tmp)->content, "|") == 0 && (*tmp)->quoted == 0)
		{
			(*tmp) = (*tmp)->next;
			break ;
		}
		if ((*tmp)->next && ft_strcmp((*tmp)->next->content, " ") == 0)
			ft_dellst(tmp, (*tmp)->next);
		(*tmp) = (*tmp)->next;
	}
}

int	ft_ncmp(char *s1)
{
	size_t	i;

	i = 1;
	if (s1 == NULL)
		return (1);
	if (s1[0] != '-' || ft_strlen(s1) == 1)
		return (1);
	while (s1[i])
	{
		if (s1[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	is_echo(t_list **tmp)
{
	while (*tmp)
	{
		if (ft_strcmp((*tmp)->content, "|") == 0 && (*tmp)->quoted == 0)
		{
			(*tmp) = (*tmp)->next;
			break ;
		}
		else if (ft_cmpecho((*tmp)->content) == 0 && (*tmp)->next
			&& ft_strcmp((*tmp)->next->content, " ") == 0)
		{
			ft_dellst(tmp, (*tmp)->next);
			if ((*tmp)->next && ft_ncmp((*tmp)->next->content) == 0)
			{
				(*tmp) = (*tmp)->next;
				if ((*tmp)->next && ft_strcmp((*tmp)->next->content, " ") == 0)
					ft_dellst(tmp, (*tmp)->next);
			}
		}
		(*tmp) = (*tmp)->next;
	}
}
