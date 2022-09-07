/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:42:55 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/07 04:18:43 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///////////////////debug//////////////////////
void	printdub(char **content)
{
	int	i;

	i = 0;
	while (content != NULL && content[i] != NULL)
	{
		printf("content[%d] = |%s|\n", i, content[i]);
		i++;
	}
	printf("content[%d] = |%s|\n", i, content[i]);
}

static void	printdub_cmd(char **content, int *quoted, t_red *red)
{
	int	i;

	i = 0;
	while (content != NULL && content[i] != NULL)
	{
		printf("content[%d] = |%s| quoted: |%d|\n", i, content[i], quoted[i]);
		i++;
	}
	printf("content[%d] = |%s|\n", i, content[i]);
	printf(">>>>redirections<<<<\n");
	while (red)
	{
		printf("type = |%d| file_name = |%s| pipe_0 |%d|\n", red->type,
			red->file_name, red->pipe_0);
		red = red->next;
	}
	printf(">>>>>>>>>><<<<<<<<<<\n");
}

void	ft_print(t_list *arg)
{
	while (arg != NULL)
	{
		printf("|%s|%d|\n", arg->content, arg->quoted);
		arg = arg->next;
	}
}

void	ft_print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd != NULL)
	{
		printdub_cmd(cmd->content, cmd->quoted, cmd->red);
		if (cmd->next)
			printf("__\n");
		cmd = cmd->next;
	}
}
//////////////////////////////////////////////

static void	check_line(char *buff, t_env *env)
{
	t_list	*arg;
	t_cmd	*cmd;

	arg = NULL;
	if (buff[0])
	{
		add_history(buff);
		if (lex(buff, &arg, env) || only_space(arg))
			ft_lstclear(&arg, free);
		else
		{
			ft_wildcard(&arg);
			cmd = split_pipe(arg);
			redirections_parser(cmd);
			//g_global exit_status=0;
			exec_all(cmd, &env);
			// ft_print(arg);////////////////////delete
			// printf("-----------------\n");////delete
			// ft_print_cmd(cmd);////////////////delete
			// printf("-----------------\n");////delete
			ft_lstclear(&arg, free);
			ft_cmdclear(&cmd, free);
		}
	}
}

void	handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **nv)
{
	char	*buff;
	t_env	*env;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	ac = 0;
	av = NULL;
	env = ft_env(nv);
	while (1)
	{
		buff = readline("\033[0;36m\e[1mminishell\e[m:~$ ");
		if (!buff)
		{
			ft_free_env(env);
			printf("exit\n");
			exit(0);
		}
		check_line(buff, env);
		free(buff);
		// system("leaks minishell");////////////delete
	}
	return (0);
}
