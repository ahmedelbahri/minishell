# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 14:49:20 by ahel-bah          #+#    #+#              #
#    Updated: 2022/06/13 21:34:13 by ahel-bah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
 
C = cc

F = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strmapi.c \
	ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_strlen.c ft_substr.c ft_toupper.c ft_tolower.c \
	ft_striteri.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJ = $(SRC:.c=.o)

BNS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c ft_lstmap.c \

BNS_OBJ = $(BNS:.c=.o)

all: $(NAME)

%.o:%.c
	$(C) $(F) -c $<

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

bonus: $(BNS_OBJ) $(OBJ)
	ar -rc $(NAME) $(BNS_OBJ) $(OBJ)

clean:
	rm -rf $(OBJ) $(BNS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all