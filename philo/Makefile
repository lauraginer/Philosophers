# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 18:14:11 by lginer-m          #+#    #+#              #
#    Updated: 2025/09/03 20:40:24 by lginer-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address
#-Wunreachable-code -Ofast \

# Debug flags
DEBUG_FLAGS = -g

# Source and object files
SRC_DIR = src/
SRC = main.c utils.c mutex.c threads.c monitor.c actions.c
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

all: $(NAME)

$(NAME): banner.flag $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)✅ Compiling Philo...$(RESET)"

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "$(YELLOW)🔧 Compiled $<$(RESET)"

clean:
	@rm -rf $(OBJS)
	@echo "$(BLUE)🧹 Object files cleaned!$(RESET)"
	@rm banner.flag

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)🔥 $(NAME) has been deleted!$(RESET)"

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: banner
	@echo "$(GREEN)🐛 Compiling in debug mode...$(RESET)"
	@make all

valgrind: debug
	@echo "$(GREEN)🔍 Running with Valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 4 410 200 200

banner.flag:
	@clear
	@echo "$(YELLOW)"
	@echo " ██████╗ ██╗  ██╗██╗██╗      ██████╗ "
	@echo " ██╔══██╗██║  ██║██║██║     ██╔═══██╗"
	@echo " ██████╔╝███████║██║██║     ██║   ██║"
	@echo " ██╔═══╝ ██╔══██║██║██║     ██║   ██║"
	@echo " ██║     ██║  ██║██║███████╗╚██████╔╝"
	@echo " ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ "
	@echo "$(RESET)"
	@touch banner.flag

.PHONY: all, clean, fclean, re, banner
