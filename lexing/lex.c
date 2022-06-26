/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:44:22 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/24 19:16:48 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	is_space(char *buff, t_lex *lex, t_list **arg)
{
	lex->argstart = lex->i;
	lex->arglen = lex->i + 1;
	while (buff[lex->i] == ' ')
		lex->i++;
	ft_lstadd_back(arg,
		ft_lstnew(ft_substr(buff, lex->argstart, lex->arglen), 0));
}

int	lex(char *buff, t_list **arg)
{
	t_lex	lex;
	t_list	*tmp;

	lex.i = 0;
	while (buff[lex.i])
	{
		if (buff[lex.i] == ' ')
			is_space(buff, &lex, arg);
		if (buff[lex.i] == '\'')
			if (single_quoting(buff, &lex, arg))
				return (1);
		if (buff[lex.i] == '"')
			if (double_quoting(buff, &lex, arg))
				return (1);
		collect_args(buff, &lex, arg);
	}
	concatenate(*arg);
	del_spaces(arg);
	tmp = *arg;
	clean_line(&tmp);
	return (0);
}
