/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:51:30 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/07 04:10:04 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	herdoc_handler(int sig)
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

static int	ft_read_herdoc(int fd[2], t_list *tmp)
{
	char	*s;

	signal(SIGINT, herdoc_handler);
	while (1)
	{
		s = readline("herdoc>");
		if (!s || ft_strcmp(tmp->next->content, s) == 0)
		{
			if (ft_strcmp(tmp->next->content, s) == 0)
				free(s);
			break ;
		}
		ft_putstr_fd(s, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(s);
	}
	close(fd[1]);
	close(fd[0]);
	exit(0);
}

void	ft_herdoc(t_list **arg)
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
				ft_read_herdoc(fd, tmp);
			close(fd[1]);
			wait(&f);
			signal(SIGINT, handler);
			if (f == 256 && !close(fd[0]))
				return ;
		}
		tmp = tmp->next;
	}
}
