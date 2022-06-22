/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:42:55 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/22 15:53:42 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_previous(t_list **lst)
// {
// 	t_list	*lst1;
// 	t_list	*lst2;

// 	lst1 = (*lst);
// 	lst2 = (*lst)->next;
// 	while (lst2 != NULL)
// 	{
// 		lst2->previous = lst1;
// 		lst1 = lst1->next;
// 		lst2 = lst2->next;
// 	}
// }

void	ft_print(t_list *arg)///////////////delete
{
	while (arg != NULL)
	{
		printf("|%s|%d|\n", arg->content, arg->quoted);
		arg = arg->next;
	}
}

void	check_line(char *buff)
{
	t_list	*arg;
	t_list	*tmp;

	arg = NULL;
	if (buff[0])
	{
		add_history(buff);
		if (lex(buff, &arg) || only_space(arg))
			ft_lstclear(&arg, free);
		// ft_previous(&arg);
		else
		{
			tmp = arg;
			clean_line(&tmp);
			ft_print(arg);
			ft_lstclear(&arg, free);
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
			exit(0);
		check_line(buff);
		free(buff);
	}
	return (0);
}
