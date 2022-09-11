/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:44:27 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/10 20:40:18 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_replace(t_list **arg, t_env *env)
{
	char	*tmp;

	while (env)
	{
		if (ft_strcmp(&(*arg)->content[1], env->name) == 0)
			break ;
		env = env->next;
	}
	if ((*arg)->content[0] == '$' && (*arg)->content[1] == '\0')
		return ;
	if (env == NULL)
		(*arg)->quoted = 4;
	else
	{
		tmp = (*arg)->content;
		(*arg)->content = ft_strdup(env->content);
		free(tmp);
	}
}

void	ft_expend(t_list **arg, t_env *env, int d)
{
	int		len;
	char	*tmp;

	len = 1;
	if (d > 0)
	{
		ft_lstinsert(arg, ft_lstnew(ft_strdup(&(*arg)->content[d]), 0));
		tmp = (*arg)->content;
		(*arg)->content = ft_substr_lex((*arg)->content, 0, d);
		free(tmp);
		return ;
	}
	while ((*arg)->content[len] != '\0' && (ft_isalpha((*arg)->content[len])
			|| (*arg)->content[len] == '_' || ft_isalnum((*arg)->content[len])))
		len++;
	if ((*arg)->content[len] != '\0')
	{
		ft_lstinsert(arg, ft_lstnew(
				ft_strdup(&((*arg)->content[len])), (*arg)->quoted));
		tmp = (*arg)->content;
		(*arg)->content = ft_substr_lex((*arg)->content, 0, len);
		free(tmp);
	}
	ft_replace(arg, env);
}

static void	ft_expand_exit_status(t_list **arg)
{
	if (ft_strlen((*arg)->content) == 2 && (*arg)->quoted != 1
		&& (*arg)->content[0] == '$' && (*arg)->content[1] == '?')
	{
		free((*arg)->content);
		(*arg)->content = ft_strdup(ft_itoa(g_exit_status));
	}
	else if ((*arg)->quoted != 1 && (*arg)->content[0] == '$'
		&& (*arg)->content[1] == '?')
	{
		ft_lstinsert(arg, ft_lstnew(ft_strdup(&(*arg)->content[2]), (*arg)->quoted));
		free((*arg)->content);
		(*arg)->content = ft_itoa(g_exit_status);
	}
}

void	dollar(t_list **arg, t_env *env)
{
	int		i;
	char	*tmp;
	int		sequenced_dollars;

	i = 0;
	sequenced_dollars = 0;
	ft_expand_exit_status(arg);
	while ((*arg)->content[i] && (*arg)->content[i] != '$')
		i++;
	if (i > 0)
	{
		ft_lstinsert(arg, ft_lstnew(ft_strdup(&(*arg)->content[i]),
				(*arg)->quoted));
		tmp = (*arg)->content;
		(*arg)->content = ft_substr_lex((*arg)->content, 0, i);
		free(tmp);
	}
	while ((*arg)->content[i++] == '$' && (*arg)->content[i] == '$')
		sequenced_dollars++;
	if ((*arg)->content[0] == '$')
		ft_expend(arg, env, sequenced_dollars);
}

void	clean_line(t_list **arg, t_env *env)
{
	t_list	*tmp;

	tmp = (*arg);
	while (tmp)
	{
		ft_is_redirections(&tmp);
		define_pipe(&tmp);
		tmp = tmp->next;
	}
	ft_herdoc(arg, env);
	while (*arg)
	{
		if (((*arg)->quoted == 0 && ft_strcmp((*arg)->content, "|") == 0
				&& (*arg)->next && (*arg)->next->quoted == 0
				&& ft_strcmp((*arg)->next->content, " ") == 0))
			ft_dellst(arg, (*arg)->next);
		if ((*arg) && (*arg)->quoted != 1 && ft_strchr((*arg)->content, '$'))
			dollar(arg, env);
		(*arg) = (*arg)->next;
	}
}
