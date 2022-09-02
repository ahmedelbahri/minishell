/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_lex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:44 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/02 01:31:57 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr_lex(char *s, unsigned int start, size_t end)
{
	char			*s1;
	unsigned int	i;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < end)
		end = ft_strlen(s);
	s1 = (char *)malloc(sizeof(char) * end + 1);
	if (s1 == 0)
		return (0);
	i = 0;
	while (start < end)
	{
		s1[i] = s[start];
		i++;
		start++;
	}
	s1[i] = '\0';
	return (s1);
}
