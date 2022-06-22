/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:42:12 by ahel-bah          #+#    #+#             */
/*   Updated: 2021/11/15 10:24:16 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*casts;
	unsigned char	castc;

	i = 0;
	casts = (unsigned char *)s;
	castc = (unsigned char)c;
	while (i < n)
	{
		if (casts[i] == castc)
		{
			return (&casts[i]);
		}
		i++;
	}
	return (0);
}
