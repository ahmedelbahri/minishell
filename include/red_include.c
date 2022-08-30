/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_include.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 04:09:06 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/08/30 04:23:19 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

t_red	*ft_rednew(char *file_name)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	if (red == 0)
		return (0);
	red->file_name = file_name;
	red->type = 0;
	red->next = NULL;
	return (red);
}

t_red	*ft_redlast(t_red *red)
{
	if (red == NULL)
		return (0);
	while (red->next != NULL)
		red = red->next;
	return (red);
}

void	ft_reddelone(t_red *red, void (*del)(void*))
{
	del(red->file_name);
	free(red);
}

void	ft_redclear(t_red **red, void (*del)(void*))
{
	t_red	*tmp;

	tmp = NULL;
	while (*red != NULL)
	{
		tmp = *red;
		*red = (*red)->next;
		ft_reddelone(tmp, del);
	}
	*red = NULL;
}

void	ft_redadd_back(t_red **red, t_red *new)
{
	t_red	*red1;

	if (*red == NULL)
	{
		*red = new;
		return ;
	}
	red1 = ft_redlast(*red);
	red1->next = new;
}
