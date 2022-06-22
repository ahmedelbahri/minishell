/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:49:11 by ahel-bah          #+#    #+#             */
/*   Updated: 2021/11/17 18:00:04 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*castdst;
	char	*castsrc;

	i = 0;
	castdst = (char *)dst;
	castsrc = (char *)src;
	if (dst == 0 && src == 0)
		return (0);
	while (n > 0)
	{
		castdst[i] = castsrc[i];
		i++;
		n--;
	}
	return (dst);
}
