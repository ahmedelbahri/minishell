/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numberize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:39:02 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/20 22:53:53 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_numberize(t_list *arg)
{
	int	i;

	i = 1;
	while (arg != NULL)
	{
		arg->num = i;
		arg = arg->next;
		i++;
	}
}
