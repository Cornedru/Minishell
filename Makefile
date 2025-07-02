# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 03:00:00 by oligrien          #+#    #+#              #
#    Updated: 2025/07/02 21:49:54 by ndehmej          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name *************************************************************** #
NAME = minishell

# Directories **************************************************************** #
SRCS_DIR =		./src
OBJS_DIR =		./obj
LIBFT_DIR =		./libft
GC_DIR =		./gc
INCLUDES_DIR =	./includes

BUILTINS_DIR = 	built-ins
UTILS_DIR =		utils
PRS_DIR =		parser

# Source Files *************************************************************** #
SRCS_FILES =	main.c \
			parser/expander.c \
			parser/expander_utils.c \
			parser/expander_utils2.c \
			parser/heredoc.c \
			parser/lexer.c \
			parser/lexer_utils.c \
			parser/parser.c \
			parser/utils3.c \
			parser/parser2.c \
			parser/clear_utils.c \
			parser/clear_utils2.c \
			parser/parser_utils.c \
			parser/parser_utils2.c \
			parser/quotes.c \
			parser/utils2.c \
			utils/utils.c \
			utils/memory.c \
			utils/memory_utils.c


SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

# libft ********************************************************************** #
LIBFT = $(LIBFT_DIR)/libft.a

# gc ************************************************************************* #
GC = $(GC_DIR)/gc.a

# Compilation **************************************************************** #
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I$(INCLUDES_DIR) -I$(LIBFT_DIR) -I$(GC_DIR)/includes

# Rules ********************************************************************** #
all: $(NAME)

# Build executable *********************************************************** #
$(NAME): $(OBJS) $(LIBFT) $(GC)
	@echo "Making" $(NAME) "..."
	@$(CC) $(CFLAGS) $(OBJS) $(GC) $(LIBFT) -o $(NAME) -lreadline
	@echo "Done."

# Build libft.a ************************************************************** #
$(LIBFT):
	@echo "Making libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "libft done."

# Build gc.a ***************************************************************** #
$(GC): $(LIBFT)
	@echo "Making gc..."
	@$(MAKE) -s -C $(GC_DIR) LIBFT_PATH="../libft"
	@echo "gc done."

# Compile .c files to .o files *********************************************** #
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean ********************************************************************** #
clean:
	@echo "Cleaning..."
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(GC_DIR) clean
	@echo "Done."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(GC_DIR) fclean

re: fclean all

# **************************************************************************** #
.PHONY: all clean fclean re