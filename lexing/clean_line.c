/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:44:27 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/23 22:09:49 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	more_dollars(char *arg, int *i)
// {
// 	while (arg[*i] && arg[*i + 1] && arg[*i] == '$' && arg[*i + 1] == '$')
// 		(*i)++;
// }

// int	end_dollars(char *arg, int i)
// {
// 	i++;
// 	while (arg[i] && arg[i] != '$')
// 		i++;
// 	return (i);
// }

// void	seperate_quoted(t_list **arg, int i)
// {
// 	t_list		*new1;
// 	t_list		*new2;
// 	char		*buff;

// 	buff = (*arg)->content;
// 	more_dollars(buff, &i);
// 	new1 = ft_lstnew(ft_substr(buff, 0, i), 2);
// 	ft_lstinsert(arg, &new1);
// 	(*arg) = (*arg)->next;
// 	new2 = ft_lstnew(ft_substr(buff, i, end_dollars(buff, i)), 2);
// 	ft_lstinsert(arg, &new2);
// 	ft_dellst(&((*arg)->previous));
// 	exit(0);
// 	// ftprint(*arg);
// 	// printf("%s", (*arg)->previous->content);
// }

// int	cout_dollars(char *arg)
// {
// 	int	i;

// 	i = 0;
// 	while (arg[i] && arg[i] == '$')
// 		i++;
// 	return (i);
// }

// void	dollar(t_list **arg)
// {
// 	int	i;

// 	i = 0;
// 	while ((*arg)->content[i] && (*arg)->content[i] != '$')
// 		i++;
// 	if (cout_dollars(&(*arg)->content[i]) > 1 && (*arg)->quoted == 2
// 		&& (*arg)->content[i] && (*arg)->content[i] == '$')
// 	{
// 		seperate_quoted(arg, i);
// 		return ;
// 	}
// 	if ((*arg)->quoted == 0 && (*arg)->content[i] && (*arg)->content[i] == '$')
// 	{
// 		// seperate(arg, i);
// 		return ;
// 	}
// }

void	clean_line(t_list **arg)
{
	t_list	*tmp;

	tmp = (*arg);
	while (tmp)
	{
		redirections(&tmp);
		define_pipe(&tmp);
		tmp = tmp->next;
	}
	while (*arg)
	{
		if (((*arg)->next && ft_strcmp((*arg)->next->content, " ") == 0
				&& (*arg)->next->quoted == 0 && (*arg)->next->next
				&& ft_is_opperator((*arg)->next->next))
			|| ((*arg)->quoted == 0 && ft_is_opperator(*arg)
				&& (*arg)->next && (*arg)->next->quoted == 0
				&& ft_strcmp((*arg)->next->content, " ") == 0))
			ft_dellst(arg, (*arg)->next);
		(*arg) = (*arg)->next;
	}
}
