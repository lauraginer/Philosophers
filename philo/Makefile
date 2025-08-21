# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 18:14:11 by lginer-m          #+#    #+#              #
#    Updated: 2025/08/21 12:43:34 by lginer-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Source and object files
SRC_DIR = src/
SRC = main.c utils.c mutex.c threads.c
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)

# Headers
HEADERS = -Iinc

# Colors for terminal output
BLUE = \033[0;34m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

all: banner $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)✅ Compiling Philo...$(RESET)"

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "$(YELLOW)🔧 Compiled $<$(RESET)"

clean:
	@rm -rf $(OBJS)
	@echo "$(BLUE)🧹 Object files cleaned!$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)🔥 $(NAME) has been deleted!$(RESET)"

re: fclean all

banner:
	@clear
	@echo "$(YELLOW)"
	@echo " ██████╗ ██╗  ██╗██╗██╗      ██████╗ "
	@echo " ██╔══██╗██║  ██║██║██║     ██╔═══██╗"
	@echo " ██████╔╝███████║██║██║     ██║   ██║"
	@echo " ██╔═══╝ ██╔══██║██║██║     ██║   ██║"
	@echo " ██║     ██║  ██║██║███████╗╚██████╔╝"
	@echo " ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ "
	@echo "$(RESET)"

.PHONY: all, clean, fclean, re, banner
