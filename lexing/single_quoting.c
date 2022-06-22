/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quoting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:42:28 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/20 22:29:51 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_quoting(char *buff, t_lex *lex, t_list **arg)
{
	lex->i++;
	if (buff[lex->i] == '\'')
	{
		lex->arglen = 0;
		lex->argstart = 0;
		ft_lstadd_back(arg,
			ft_lstnew(ft_substr(buff, lex->argstart, lex->arglen), 1));
		lex->i++;
		return (0);
	}
	lex->argstart = lex->i;
	while (buff[lex->i])
	{
		if (buff[lex->i] == '\'')
		{
			lex->arglen = lex->i;
			ft_lstadd_back(arg,
				ft_lstnew(ft_substr(buff, lex->argstart, lex->arglen), 1));
			lex->i++;
			return (0);
		}
		lex->i++;
	}
	perror("orrror");
	return (1);
}
