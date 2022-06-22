/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:23:40 by ahel-bah          #+#    #+#             */
/*   Updated: 2021/11/13 11:31:24 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	k;
	size_t	srcsize;
	size_t	srcbefore;

	i = 0;
	srcsize = 0;
	srcbefore = 0;
	while (dst[i] != '\0')
		i++;
	while (src[srcsize] != '\0')
		srcsize++;
	if (dstsize < i)
		return (dstsize + srcsize);
	k = srcsize + i;
	while (src[srcbefore] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[srcbefore];
		i++;
		srcbefore++;
	}
	dst[i] = '\0';
	return (k);
}
