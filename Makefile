# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 18:27:35 by vgoyzuet          #+#    #+#              #
#    Updated: 2025/01/16 19:17:40 by vgoyzuet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S = server
NAME_C = client

CC = cc
CFLAGS = -Wall -Wextra -Werror -I libft

LIBFT = libft/libft.a

SRCS_S = src/server/server.c\
	src/server/main.c\

SRCS_C = @echo "client don't exit yet"
# src/client/client.c\
# src/client/main.c\

OBJ_S = $(SRCS_S:%.c=objs/%.o)
OBJ_C = $(SRCS_C:%.c=objs/%.o)

all: $(NAME_S) $(NAME_C)

$(NAME_S): objs $(OBJ_S)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ_S) $(LIBFT) -o $(NAME_S)
	@echo "Server ready"

$(NAME_C): objs $(OBJ_C)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ_C) $(LIBFT) -o $(NAME_C)
	@echo "Client ready"

objs:
	@mkdir -p objs/src/server objs/src/client

objs/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C libft
	@rm -rf objs
	@echo "Objetcs files deleted."

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME_S)
	@rm -f $(NAME_C)
	@echo "Full clean completed"

re: fclean all

.PHONY: all clean fclean re
