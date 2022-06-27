/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:42:55 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/27 13:23:11 by ahel-bah         ###   ########.fr       */
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
		printf("%i content[i] = |%s|\n", i, content[i]);
		i++;
	}
	printf("%i content[i] = |%s|\n", i, content[i]);
}

void	ft_print(t_list *arg)
{
	while (arg != NULL)
	{
		printf("|%s|\n", arg->content);
		arg = arg->next;
	}
}

void	ft_print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd != NULL)
	{
		printdub(cmd->content);
		if (cmd->next)
			printf("__\n");
		cmd = cmd->next;
	}
}
//////////////////////////////////////////////

void	check_line(char *buff)
{
	t_list	*arg;
	t_cmd	*cmd;

	arg = NULL;
	if (buff[0])
	{
		add_history(buff);
		if (lex(buff, &arg) || only_space(arg))
			ft_lstclear(&arg, free);
		else
		{
			cmd = split_pipe(arg);
			ft_print(arg);
			ft_lstclear(&arg, free);
			printf("-----------------\n");
			ft_print_cmd(cmd);
			printf("-----------------\n");
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

int	main(int ac, char *av[], char *env[])
{
	char	*buff;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	ac = 0;
	av = NULL;
	env = NULL;
	while (1)
	{
		buff = readline("\033[0;34m\e[1mminishell\e[m\
@\033[0;32m\e[1mahel-bah\e[m:~$ ");
		if ((!buff) || ft_strcmp(buff, "exit") == 0)
		{
			printf("exit\n");
			exit(0);
		}
		check_line(buff);
		free(buff);
	}
	return (0);
}
