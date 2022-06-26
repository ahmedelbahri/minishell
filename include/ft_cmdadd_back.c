/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:02:03 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/26 19:02:31 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*cmd1;

	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	cmd1 = ft_cmdlast(*cmd);
	cmd1->next = new;
}
