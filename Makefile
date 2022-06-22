# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 15:18:51 by ahel-bah          #+#    #+#              #
#    Updated: 2022/06/22 19:40:03 by ahel-bah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
NAME = minishell
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = minishell.c \
\
	  lexing/single_quoting.c lexing/double_quoting.c lexing/collect_args.c \
	  lexing/lex.c lexing/concatenate.c \
\
	  parsing/clean_line.c parsing/define_opp.c \
\
	  include/ft_strcmp.c include/ft_lstinsert.c include/ft_dellst.c \
	  include/spaces.c include/ft_numberize.c include/ft_is_operator.c

OBJ = $(SRC:.c=.o)
	
%.o:%.c
	$(CC) $(CFLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@
	
all: $(LIBFT) $(NAME) 

$(NAME): $(OBJ)
	$(CC)  $(OBJ) -L$(shell brew --prefix readline)/lib -lreadline -o $(NAME) $(LIBFT)

$(LIBFT):
	@$(shell cd libft && make fclean && make bonus && make clean)

fcleanlib:
	@$(shell cd libft && make fclean)

update:
	$(shell cd ~/goinfre && brew update)

upgrade:
	$(shell cd ~/goinfre && brew upgrade)

install:
	$(shell cd ~/goinfre && brew install readline)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# @echo "\033[1;33m"Hint:"\033[0m" in case of error you may run this command first "\033[1;36m"make lib"\033[0m"