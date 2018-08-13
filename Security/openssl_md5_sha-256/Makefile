# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pstringe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/02 14:49:53 by pstringe          #+#    #+#              #
#    Updated: 2018/08/03 11:06:40 by pstringe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = openssl
INCD = ./includes/
LIB = libft.a
INCD = ./includes/
SRCD = ./srcs/
LIBD = $(INCD)libft/
SRCS = openssl.c
OBJS = $(patsubst $(SRCD)%, %.o, $(SRCS))
CFLAGS = -Wall -Werror -Wextra
DFLAGS = -g
SFLAGS = -fsanitize -fno-omit-frame-pointer

all: $(NAME)
$(NAME): $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(patsubst %, $(SRCD)%.c, $(SRCS)) -L$(LIBD) -lft -I $(INCD) 
debug: fclean $(LIB)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(NAME) $(patsubst %, $(SRCD)%.c, $(SRCS)) -L$(LIBD) -lft -I $(INCD)
sanitize: fclean $(LIB)
	$(CC) $(CFLAGS) $(SFLAGS) -o $(NAME) $(patsubst %, $(SRCD)%.c, $(SRCS)) -L$(LIBD) -lft -I $(INCD)
$(LIB):
	make -C libft
clean:
	make -C libft clean
	rm -rf *.o
	rm -rf *.dSYM
fclean: clean
	make -C libft fclean
	rm -rf $(NAME)
re: fclean
	$(NAME)

