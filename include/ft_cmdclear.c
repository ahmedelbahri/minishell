/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:04:31 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/26 19:04:50 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmdclear(t_cmd **cmd, void (*del)(void*))
{
	t_cmd	*tmp;

	tmp = NULL;
	while (*cmd != NULL)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		ft_cmddelone(tmp, del);
	}
	*cmd = NULL;
}
