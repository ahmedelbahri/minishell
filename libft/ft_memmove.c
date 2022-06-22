/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:21:43 by ahel-bah          #+#    #+#             */
/*   Updated: 2021/11/21 21:38:20 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void	*dst, const	void *src, size_t len)
{
	size_t	i;
	char	*castdst;
	char	*castsrc;

	i = 0;
	castdst = (char *)dst;
	castsrc = (char *)src;
	if (dst == 0 && src == 0)
		return (0);
	while (len > 0 && castdst > castsrc)
	{
		castdst[len - 1] = castsrc[len - 1];
		len--;
	}
	while (len > 0)
	{
		castdst[i] = castsrc[i];
		i++;
		len--;
	}
	return (dst);
}
