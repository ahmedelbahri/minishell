/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dubstr_include.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:01:31 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/07/29 18:18:49 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dubstrlen(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

void	free_dub(char **content)
{
	int	i;
	int	len;

	if (content == NULL)
		return ;
	i = 0;
	len = ft_dubstrlen(content);
	while (i < len)
	{
		free(content[i]);
		i++;
	}
	free(content);
}

int	*remove_array_column(int *arr, int arr_size, int col)
{
	int	i;
	int	i_old;
	int	*new_arr;

	i = 0;
	i_old = 0;
	new_arr = malloc(sizeof(int) * (arr_size - 1));
	if (arr == NULL)
		return (0);
	while (i_old < arr_size)
	{
		if (i_old == col)
			i_old++;
		else
		{
			new_arr[i] = arr[i_old];
			i++;
			i_old++;
		}
	}
	free(arr);
	return (new_arr);
}

char	**reallocate_dub(char **content, char *arg_content)
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

char	**remove_str(char **content, int remove_index)
{
	char	**new_content;
	int		content_len;
	int		i;
	int		i_old;

	if (content == NULL)
		return (0);
	content_len = ft_dubstrlen(content);
	new_content = malloc(sizeof(char *) * content_len);
	i = 0;
	i_old = 0;
	while (i_old < content_len)
	{
		if (i_old == remove_index)
			i_old++;
		else if (i_old < content_len)
		{
			new_content[i] = ft_strdup(content[i_old]);
			i++;
			i_old++;
		}
	}
	new_content[i] = NULL;
	free_dub(content);
	return (new_content);
}
