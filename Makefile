# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 18:27:35 by vgoyzuet          #+#    #+#              #
#    Updated: 2025/01/22 20:13:03 by vgoyzuet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN	=	\033[1;32m
CYAN	=	\033[0;36m
WHITE	=	\033[0m
CLEAR	=	\r\033[K

NAME_S = server
NAME_C = client

CC = cc
CFLAGS = -Wall -Wextra -Werror -I libft

LIBFT = libft/libft.a

SRCS_S = src/server/server.c\
	src/server/main.c\

SRCS_C = src/client/client.c\
	src/client/main.c\

OBJ_S = $(SRCS_S:%.c=objs/%.o)
OBJ_C = $(SRCS_C:%.c=objs/%.o)

all: $(LIBFT) $(NAME_S) $(NAME_C)

$(NAME_S): objs $(OBJ_S)
	@$(CC) $(CFLAGS) $(OBJ_S) $(LIBFT) -o $(NAME_S)
	@echo "$(GREEN)Server ready$(WHITE)"

$(NAME_C): objs $(OBJ_C)
	@$(CC) $(CFLAGS) $(OBJ_C) $(LIBFT) -o $(NAME_C)
	@echo "$(GREEN)Client ready$(WHITE)"
	
$(LIBFT):
	@make --silent -C libft

objs:
	@mkdir -p objs/src/server objs/src/client

objs/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make --silent clean -C libft
	@rm -rf objs
	@echo "Objetcs files deleted."

fclean: clean
	@make --silent fclean -C libft
	@rm -f $(NAME_S)
	@rm -f $(NAME_C)
	@echo "Full clean completed"

re: fclean all

.PHONY: all clean fclean re
