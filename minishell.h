/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:06:52 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/27 13:55:04 by ahel-bah         ###   ########.fr       */
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

typedef struct s_cmd
{
	char			**content;
	int				quoted;
	struct s_cmd	*next;
}				t_cmd;

int		single_quoting(char *buff, t_lex *lex, t_list **arg);
int		double_quoting(char *buff, t_lex *lex, t_list **arg);
void	collect_args(char *buff, t_lex *lex, t_list **arg);
char	**reallocate_cmd(char **content, char *arg_content);
int		lex(char *buff, t_list **arg);
void	clean_line(t_list **arg);
int		ft_dubstrlen(char **s);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_lstinsert(t_list **lst, t_list *new);
void	ft_dellst(t_list **lst, t_list *del);
int		only_space(t_list *arg);
void	ft_cmdclear(t_cmd **cmd, void (*del)(void*));
int		ft_is_opperator(t_list *arg);
void	define_pipe(t_list **arg);
void	redirections(t_list **arg);
void	del_spaces(t_list **arg);
void	concatenate(t_list *arg);
t_cmd	*split_pipe(t_list *arg);
t_cmd	*ft_cmdlast(t_cmd *cmd);
t_cmd	*ft_cmdnew(char **content, int quoted);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
void	ft_cmddelone(t_cmd *cmd, void (*del)(void*));
void	printdub(char **content);///////////////////////////////delete
void	ft_print_cmd(t_cmd *cmd);///////////////////////////////delete
void	ft_print(t_list *arg);//////////////////////////////////delete
////////////////////////////////////////////////////////////////matnsash libft.a

#endif