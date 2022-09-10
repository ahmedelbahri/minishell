/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:51:30 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/10 22:41:45 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	exit(1);
}

static int	ft_get_in(t_list *tmp)
{
	if (ft_strcmp(tmp->content, "<<") == 0 && tmp->quoted == 0)
	{
		if (tmp->next && ft_strcmp(tmp->next->content, " ") == 0
			&& tmp->next->quoted == 0)
			ft_dellst(&tmp, tmp->next);
		if (tmp->next == NULL || (tmp->next && ft_is_opp(tmp->next)
				&& tmp->next->quoted == 0))
			return (0);
		return (1);
	}
	return (0);
}

static char	*herdoc_dollar(char *s, t_env *env)
{
	char	*ret;
	t_list	*arg;
	t_list	*tmp;

	arg = ft_lstnew(ft_strdup(s), 0);
	free(s);
	tmp = arg;
	while (tmp)
	{
		dollar(&tmp, env);
		tmp = tmp->next;
	}
	tmp = arg;
	ret = ft_strdup("");
	while (tmp)
	{
		s = ret;
		ret = ft_strjoin(ret, tmp->content);
		free(s);
		tmp = tmp->next;
	}
	ft_lstclear(&arg, free);
	return (ret);
}

static int	ft_read_herdoc(int fd[2], t_list *tmp, t_env *env)
{
	char	*s;

	concatenate(&tmp);
	signal(SIGINT, cmd_handler);
	while (1)
	{
		s = readline("herdoc>");
		if (!s || ft_strcmp(tmp->next->content, s) == 0)
		{
			if (ft_strcmp(tmp->next->content, s) == 0)
				free(s);
			break ;
		}
		if (ft_strchr(s, '$') && tmp->next->quoted == 0)
			s = herdoc_dollar(s, env);
		ft_putstr_fd(s, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(s);
	}
	close(fd[1]);
	close(fd[0]);
	exit(0);
}

int	ft_herdoc(t_list **arg, t_env *env)
{
	int		f;
	int		fd[2];
	t_list	*tmp;

	tmp = (*arg);
	while (tmp)
	{
		if (ft_get_in(tmp))
		{
			pipe(fd);
			tmp->pipe_0 = fd[0];
			signal(SIGINT, SIG_IGN);
			f = fork();
			if (!f)
				ft_read_herdoc(fd, tmp, env);
			close(fd[1]);
			wait(&f);
			signal(SIGINT, handler);
			if (f != 0 && !close(fd[0]))
				return (g_exit_status = 1, 0);
		}
		tmp = tmp->next;
	}
	return (0);
}
