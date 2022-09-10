/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 23:19:54 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/10 23:24:32 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_file(t_red *red, int fd)
{
	if (red->type == HERDOC)
	{
		dup2(red->pipe_0, 0);
		close(red->pipe_0);
	}
	else if (red->type == INFILE)
	{
		fd = open(red->file_name, O_RDONLY);
		if (fd < 0)
			return (0);
		dup2(fd, 0);
		close(fd);
	}
	else
	{
		if (red->type == APPAND)
			fd = open(red->file_name, O_APPEND | O_CREAT | O_WRONLY, 0666);
		else
			fd = open(red->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			return (0);
		dup2(fd, 1);
		close(fd);
	}
	return (1);
}

int	check_redirections(t_red *redirection)
{
	int		fd;
	t_red	*red;

	fd = 0;
	red = redirection;
	while (red)
	{
		if (create_file(red, fd) == 0)
		{
			g_exit_status = 1;
			write(2, "minisehll: ", 11);
			perror(red->file_name);
			return (0);
		}
		red = red->next;
	}
	return (1);
}
