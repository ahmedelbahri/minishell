/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:06:52 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/07/23 17:56:12 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NONE 0
# define STD_IN 0
# define STD_OUT 1
# define INFILE 10
# define OUTFILE 11
# define HERDOC 12
# define APPAND 13

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
	int				*quoted;
	t_red			*red;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}				t_env;

//....................../built-ins/.....................
//./built-ins/ft_env.c
t_env	*ft_env(char **nv);
//....................../include/.......................
//./include/ft_cmd_include.c
t_cmd	*ft_cmdlast(t_cmd *cmd);
t_cmd	*ft_cmdnew(char **content, int *quoted);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
void	ft_cmddelone(t_cmd *cmd, void (*del)(void*));
void	ft_cmdclear(t_cmd **cmd, void (*del)(void*));
//./include/dellst.c
void	ft_dellst(t_list **lst, t_list *del);
//./include/ft_dubstrlen.c
int		ft_dubstrlen(char **s);
//./include/ft_env_include.c
t_env	*ft_envnew(char *content, char *name);
t_env	*ft_envlast(t_env *env);
void	ft_envadd_back(t_env **env, t_env *new);
void	ft_envdelone(t_env *env, void (*del)(void*));
void	ft_envclear(t_env **env, void (*del)(void*));
//./include/ft_env_tools.c
void	ft_free_env(t_env *env);
void	print_env(t_env *env);
//./include/ft_is_opp.c
int		ft_is_opp(t_list *arg);
//./include/ft_lstinsert.c
void	ft_lstinsert(t_list **lst, t_list *new);
//./include/ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);
//./include/in_between_include.c
void	del_in_between(t_list **tmp);
int		ft_cmpecho(const char *s);
void	is_echo(t_list **tmp);
//....................../lexing/........................
//./lexing/clean_line.c
void	clean_line(t_list **arg, t_env *env);
//./lexing/collect_args.c
void	collect_args(char *buff, t_lex *lex, t_list **arg);
//./lexing/concatenate.c
void	concatenate(t_list *arg);
//./lexing/define_opp.c
void	free_dub(char **content);
void	define_pipe(t_list **arg);
void	redirections(t_list **arg);
//./lexing/double_quoting.c
int		double_quoting(char *buff, t_lex *lex, t_list **arg);
//./lexing/single_quoting.c
int		lex(char *buff, t_list **arg, t_env *env);
//./lexing/lex.c
int		single_quoting(char *buff, t_lex *lex, t_list **arg);
//./lexing/spaces.c
int		only_space(t_list *arg);
void	del_spaces(t_list **arg);
//....................../parsing/.......................
//./parsing/ft_errors.c
//./parsing/ft_red.c
// void	ft_red(t_list *arg);
//./parsing/splite_pipe.c
t_cmd	*split_pipe(t_list *arg);
int		ft_errors(t_list **arg);
//./minishell.c
void	printdub(char **content);///////////////////////////////delete
void	ft_print_cmd(t_cmd *cmd);///////////////////////////////delete
void	ft_print(t_list *arg);//////////////////////////////////delete

#endif