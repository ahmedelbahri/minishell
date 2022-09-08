/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:25:19 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/08 17:55:19 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char **content)
{
	int	i;
	int	yes;

	i = 1;
	yes = 0;
	while (ft_ncmp(content[i]) == 0)
	{
		i++;
		yes++;
		if (content[i] && !ft_strcmp(content[i], " "))
			i++;
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
