/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:47:47 by ahel-bah          #+#    #+#             */
/*   Updated: 2021/11/15 10:30:11 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const	*s1, char const	*s2)
{
	char	*al;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	al = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (al == 0)
		return (0);
	i = 0;
	j = 0;
	while (i <= ft_strlen(s1) + ft_strlen(s2))
	{
		while (i < ft_strlen(s1))
		{
			al[i] = s1[i];
			i++;
		}
		al[i] = s2[j];
		i++;
		j++;
	}
	al[i] = '\0';
	return (al);
}
