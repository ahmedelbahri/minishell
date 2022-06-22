/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:06:52 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/22 14:26:44 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_lex
{
	int		i;
	int		arglen;
	int		argstart;
}				t_lex;

int		single_quoting(char *buff, t_lex *lex, t_list **arg);
int		double_quoting(char *buff, t_lex *lex, t_list **arg);
void	collect_args(char *buff, t_lex *lex, t_list **arg);
int		lex(char *buff, t_list **arg);
int		clean_line(t_list **arg);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_lstinsert(t_list **lst, t_list *new);
void	ft_dellst(t_list **lst, t_list *del);
int		only_space(t_list *arg);
int		ft_is_opperator(t_list *arg);
void	ft_numberize(t_list *arg);//////////////////////////////delete
void	define_pipe(t_list **arg);
void	redirections(t_list **arg);
void	del_spaces(t_list **arg);
void	concatenate(t_list *arg);
void	ft_print(t_list *arg);/////////////////////////////////delete

#endif