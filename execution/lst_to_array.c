/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:03:51 by waelhamd          #+#    #+#             */
/*   Updated: 2022/09/02 08:06:51 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	list_size(t_env *lst)
{
	int		i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**lst_to_array(t_env *env)
{
	t_env	*tmp = env;
	char	**array;
	int		i;

	i = list_size(tmp);
	array = (char **)malloc(sizeof(char *) * i + 1);
	if (!array)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp) 
	{
		array[i] = ft_strjoin(tmp->name, ft_strjoin("=", tmp->content));
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}