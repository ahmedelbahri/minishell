/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocate_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:24:53 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/26 19:08:53 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_dub(char **content)
{
	int	i;
	int	len;

	i = 0;
	len = ft_dubstrlen(content);
	while (i < len)
	{
		free(content[i]);
		i++;
	}
	free(content);
}

char	**reallocate_cmd(char **content, char *arg_content)
{
	char	**new_content;
	int		content_len;
	int		i;

	if (content == NULL)
	{
		new_content = malloc(sizeof(char *) * 2);
		new_content[0] = ft_strdup(arg_content);
		new_content[1] = NULL;
	}
	else
	{
		content_len = ft_dubstrlen(content);
		new_content = malloc(sizeof(char *) * (content_len + 2));
		i = 0;
		while (i < content_len)
		{
			new_content[i] = ft_strdup(content[i]);
			i++;
		}
		new_content[i++] = ft_strdup(arg_content);
		new_content[i] = NULL;
		free_dub(content);
	}
	return (new_content);
}
