# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 15:18:51 by ahel-bah          #+#    #+#              #
#    Updated: 2022/07/23 17:56:40 by ahel-bah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
NAME = minishell
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRC = minishell.c \
\
	  lexing/single_quoting.c lexing/double_quoting.c lexing/collect_args.c\
	  lexing/lex.c lexing/concatenate.c lexing/clean_line.c\
	  lexing/define_opp.c lexing/spaces.c\
\
	  parsing/split_pipe.c parsing/ft_red.c parsing/ft_errors.c\
\
	  include/ft_strcmp.c include/ft_lstinsert.c include/ft_dellst.c\
	  include/ft_is_opp.c include/ft_cmd_include.c\
	  include/ft_dubstrlen.c include/in_between_include.c\
	  include/ft_env_include.c include/ft_env_tools.c\
\
	  built-ins/ft_env.c

OBJ = $(SRC:.c=.o)
	
%.o:%.c
	$(CC) $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@
	
all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(OBJ) -L $(shell brew --prefix readline)/lib -lreadline -o \
	$(NAME) $(LIBFT)

$(LIBFT):
	make bonus -C libft

update:
	$(shell cd ~/goinfre && brew update)

install:
	$(shell cd ~/goinfre && brew install readline)

clean:
	$(RM) $(OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

# @echo "\033[1;33m"Hint:"\033[0m" in case of error you may run this command first "\033[1;36m"make lib"\033[0m"
# find . -type file -name "*.c"
# -fsanitize=address -static-libsan