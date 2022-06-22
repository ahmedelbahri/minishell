/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:58:28 by ahel-bah          #+#    #+#             */
/*   Updated: 2021/11/15 10:25:20 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*casts1;
	unsigned char	*casts2;

	i = 0;
	casts1 = (unsigned char *)s1;
	casts2 = (unsigned char *)s2;
	while (i < n)
	{
		if (casts1[i] != casts2[i])
		{
			return (casts1[i] - casts2[i]);
		}
		i++;
	}
	return (0);
}
