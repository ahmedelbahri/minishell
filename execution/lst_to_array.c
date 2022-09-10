/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:03:51 by waelhamd          #+#    #+#             */
/*   Updated: 2022/09/10 23:33:25 by ahel-bah         ###   ########.fr       */
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

char	**lst_to_array(t_env *env, char *save)
{
	t_env	*tmp;
	char	**array;
	int		i;

	tmp = env;
	i = list_size(tmp);
	array = (char **)malloc(sizeof(char *) * i + 1);
	if (!array)
		return (NULL);
	i = 0;
	while (tmp)
	{
		save = ft_strjoin("=", tmp->content);
		array[i] = ft_strjoin(tmp->name, save);
		free(save);
		save = NULL;
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
