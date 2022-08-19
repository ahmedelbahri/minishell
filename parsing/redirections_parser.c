/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:09:07 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/08/02 14:55:54 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_outfile_or_appand(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->red.out = NULL;
	while (cmd->content[i])
	{
		if ((ft_strcmp(cmd->content[i], ">") == 0
				|| ft_strcmp(cmd->content[i], ">>") == 0)
			&& cmd->quoted[i] == 0)
		{
			if (ft_strcmp(cmd->content[i], ">") == 0)
				cmd->red.out_type = OUTFILE;
			else if (ft_strcmp(cmd->content[i], ">>") == 0)
				cmd->red.out_type = APPAND;
			cmd->quoted = remove_array_column(cmd->quoted,
					ft_dubstrlen(cmd->content), i);
			cmd->content = remove_str(cmd->content, i);
			cmd->red.out = reallocate_dub(cmd->red.out, cmd->content[i]);
			cmd->quoted = remove_array_column(cmd->quoted,
					ft_dubstrlen(cmd->content), i);
			cmd->content = remove_str(cmd->content, i);
			i--;
		}
		i++;
	}
}

static void	ft_infile(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->red.in = NULL;
	while (cmd->content[i])
	{
		if (ft_strcmp(cmd->content[i], "<") == 0 && cmd->quoted[i] == 0)
		{
			cmd->red.in_type = INFILE;
			cmd->quoted = remove_array_column(cmd->quoted,
					ft_dubstrlen(cmd->content), i);
			cmd->content = remove_str(cmd->content, i);
			if (cmd->red.in != NULL)
				free(cmd->red.in);
			cmd->red.in = ft_strdup(cmd->content[i]);
			cmd->quoted = remove_array_column(cmd->quoted,
					ft_dubstrlen(cmd->content), i);
			cmd->content = remove_str(cmd->content, i);
			i--;
		}
		i++;
	}
}

static void	ft_herdoc(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->red.delimiter = NULL;
	while (cmd->content[i])
	{
		if (ft_strcmp(cmd->content[i], "<<") == 0 && cmd->quoted[i] == 0)
		{
			cmd->quoted = remove_array_column(cmd->quoted,
					ft_dubstrlen(cmd->content), i);
			cmd->content = remove_str(cmd->content, i);
			cmd->red.delimiter = reallocate_dub(cmd->red.delimiter,
					cmd->content[i]);
			cmd->quoted = remove_array_column(cmd->quoted,
					ft_dubstrlen(cmd->content), i);
			cmd->content = remove_str(cmd->content, i);
			i--;
		}
		i++;
	}
}

void	redirections_parser(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->red.in = NULL;
		cmd->red.out_type = STD_OUT;
		cmd->red.in_type = STD_IN;
		ft_outfile_or_appand(cmd);
		ft_infile(cmd);
		ft_herdoc(cmd);
		cmd = cmd->next;
	}
}
