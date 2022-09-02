/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:25:19 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/02 04:06:17 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char **content)
{
	int	i;
	int	yes;

	i = 1;
	yes = 0;
	if (ft_ncmp(content[i]) == 0)
	{
		i++;
		yes++;
	}
	while (content[i])
	{
		printf("%s", content[i]);
		i++;
	}
	if (yes == 0)
		printf("\n");
	return (0);
}
