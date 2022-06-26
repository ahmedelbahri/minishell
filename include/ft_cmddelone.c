/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmddelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:03:34 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/26 19:03:59 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmddelone(t_cmd *cmd, void (*del)(void*))
{
	int	i;
	int	len;

	i = 0;
	len = ft_dubstrlen(cmd->content);
	while (i < len)
	{
		del(cmd->content[i]);
		i++;
	}
	del(cmd->content);
	free(cmd);
}
