/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:37:24 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/07 04:07:51 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content, int quoted)
{
	t_list	*moh;

	moh = malloc(sizeof(t_list));
	if (moh == 0)
		return (0);
	moh->content = content;
	moh->quoted = quoted;
	moh->pipe_0 = 0;
	moh->next = NULL;
	return (moh);
}
