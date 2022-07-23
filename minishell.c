/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:42:55 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/07/23 17:54:36 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//////////////////delete//////////////////////
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

void	printdub_cmd(char **content, int *quoted)
{
	int	i;

	i = 0;
	while (content != NULL && content[i] != NULL)
	{
		printf("content[%d] = |%s| quoted: |%d|\n", i, content[i], quoted[i]);
		i++;
	}
	printf("content[%d] = |%s|\n", i, content[i]);
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
		printdub_cmd(cmd->content, cmd->quoted);
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
			// ft_red(arg);
			cmd = split_pipe(arg);
			//////////////////////////////////waelhamd
			ft_print(arg);////////////////////delete
			printf("-----------------\n");////delete
			ft_print_cmd(cmd);////////////////delete
			printf("-----------------\n");////delete
			ft_lstclear(&arg, free);
			ft_cmdclear(&cmd, free);
		}
	}
}

static void	handler(int sig)
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
	signal(SIGQUIT, handler);
	ac = 0;
	av = NULL;
	env = ft_env(nv);
	print_env(env);///////////////////////////delete
	while (1)
	{
		buff = readline("\033[0;36m\e[1mminishell\e[m:~$ ");
		if ((!buff) || ft_strcmp(buff, "exit") == 0)
		{
			ft_free_env(env);
			printf("exit\n");
			exit(0);
		}
		check_line(buff, env);
		free(buff);
		system("leaks minishell");////////////delete
	}
	return (0);
}
