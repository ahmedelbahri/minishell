/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_opp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:46:18 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/01 17:17:31 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	reallocate(t_list **arg, char *new)
{
	free((*arg)->content);
	(*arg)->content = new;
}

static void	insert_allocat(t_list **arg, int i)
{
	ft_lstinsert(arg, ft_lstnew(ft_substr_lex((*arg)->content, i,
				ft_strlen((*arg)->content)), 0));
	reallocate(arg, ft_substr_lex((*arg)->content, 0, i));
}

static int	ft_tbd(t_list **arg, int *i, char c)
{
	if ((*i) == 0 && (*arg)->content[(*i)] == c)
	{
		(*i)++;
		if ((*arg)->content[(*i)] == c)
		{
			(*i)++;
			if ((*arg)->content[(*i)] != '\0')
				insert_allocat(arg, (*i));
		}
		else if ((*arg)->content[(*i)])
			insert_allocat(arg, (*i));
		return (1);
	}
	return (0);
}

void	ft_is_redirections(t_list **arg)
{
	int	i;

	i = 0;
	while ((*arg)->quoted == 0 && (*arg)->content[i])
	{
		if (ft_tbd(arg, &i, '<') || ft_tbd(arg, &i, '>'))
			break ;
		else if ((*arg)->content[i] == '>' || (*arg)->content[i] == '<')
		{
			insert_allocat(arg, i);
			break ;
		}
		i++;
	}
}

void	define_pipe(t_list **arg)
{
	int	i;

	i = 0;
	while ((*arg)->quoted == 0 && (*arg)->content[i])
	{
		if (i == 0 && (*arg)->content[i] == '|')
		{
			i++;
			if ((*arg)->content[i])
				insert_allocat(arg, i);
			break ;
		}
		else if ((*arg)->content[i] == '|')
		{
			insert_allocat(arg, i);
			break ;
		}
		i++;
	}
}
