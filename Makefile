# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 12:19:10 by nlouis            #+#    #+#              #
#    Updated: 2025/04/17 16:15:04 by nlouis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                         PHILO MAKEFILE 🍝                                    #
# **************************************************************************** #

# Compiler settings
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g -fsanitize=thread -pthread -I include

# Binary output
NAME    := philo
BINDIR  := bin
BIN     := $(BINDIR)/$(NAME)

# Source and object files
SRCDIR  := srcs
OBJDIR  := objs
SRCS    := $(shell find $(SRCDIR) -name "*.c")
OBJS    := $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

# Colors
GREEN   := \033[0;32m
CYAN    := \033[0;36m
YELLOW  := \033[1;33m
RESET   := \033[0m

# Default goal
.DEFAULT_GOAL := all

# Build rules
all: $(BIN)

$(BIN): $(OBJS)
	@mkdir -p $(BINDIR)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "$(CYAN)🍝 Built executable:$(RESET) $(NAME)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)🛠️  Compiled:$(RESET) $<"

clean:
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)🧹 Cleaned object files.$(RESET)"

fclean: clean
	@rm -rf $(BIN) $(BINDIR)
	@echo "$(YELLOW)🗑️  Removed executable and bin/ directory.$(RESET)"

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                💡 USAGE GUIDE                                #
# **************************************************************************** #
# make            → Compile all source files and build philo 🍝
# make clean      → Remove all object files 🧹
# make fclean     → Remove object files, binary, and bin/ folder 🗑️
# make re         → Fully clean and recompile everything 🔁
# **************************************************************************** #
