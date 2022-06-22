/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:41:59 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/12 20:47:35 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;

	if (lst)
	{
		res = ft_lstnew(f(lst->content), 0);
		if (!res)
		{
			ft_lstclear(&res, del);
			return (res);
		}
		res->next = ft_lstmap(lst->next, f, del);
		return (res);
	}
	return (NULL);
}
