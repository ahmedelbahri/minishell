/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:12:14 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/16 14:20:01 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	collect_args(char *buff, t_lex *lex, t_list **arg)
{
	int	i;

	i = 0;
	while (buff[lex->i] && buff[lex->i] != '\''
		&& buff[lex->i] != '"' && buff[lex->i] != ' ')
	{
		if (i++ == 0)
			lex->argstart = lex->i;
		lex->i++;
	}
	lex->arglen = lex->i;
	if (i > 0)
		ft_lstadd_back(arg,
			ft_lstnew(ft_substr(buff, lex->argstart, lex->arglen), 0));
}
