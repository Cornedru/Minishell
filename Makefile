# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 03:00:00 by oligrien          #+#    #+#              #
#    Updated: 2025/07/06 06:07:54 by ndehmej          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name **************************************************************** #
NAME = minishell

# Directories ***************************************************************** #
SRCS_DIR     = ./src
OBJS_DIR     = ./obj
LIBFT_DIR    = ./libft
GC_DIR       = ./gc
INCLUDES_DIR = ./includes

# Subdirectories of src/ ***************************************************** #
EXEC_DIR     = exec
BUILTINS_DIR = built-ins
UTILS_DIR    = utils
PRS_DIR      = parser

# Source Files *************************************************************** #
SRCS_FILES =	../test_parsing.c \
                $(EXEC_DIR)/exec.c \
                $(EXEC_DIR)/exec_cmd.c \
                $(EXEC_DIR)/exec_builtin.c \
                $(EXEC_DIR)/pipe.c \
                $(EXEC_DIR)/path.c \
                $(EXEC_DIR)/redir.c \
                $(EXEC_DIR)/env.c \
                $(EXEC_DIR)/env_utils.c \
                $(BUILTINS_DIR)/echo.c \
                $(BUILTINS_DIR)/pwd.c \
                $(BUILTINS_DIR)/cd.c \
                $(PRS_DIR)/expander.c \
                $(PRS_DIR)/expander_utils.c \
                $(PRS_DIR)/expander_utils2.c \
                $(PRS_DIR)/heredoc.c \
                $(PRS_DIR)/lexer.c \
                $(PRS_DIR)/lexer_utils.c \
                $(PRS_DIR)/parser.c \
                $(PRS_DIR)/utils3.c \
                $(PRS_DIR)/parser2.c \
				$(PRS_DIR)/parse4.c \
                $(PRS_DIR)/clear_utils.c \
                $(PRS_DIR)/clear_utils2.c \
                $(PRS_DIR)/parser_utils.c \
                $(PRS_DIR)/parser_utils2.c \
                $(PRS_DIR)/parser_utils4.c \
                $(PRS_DIR)/quotes.c \
				$(PRS_DIR)/extra.c \
				$(PRS_DIR)/extra2.c \
                $(PRS_DIR)/utils2.c \
                $(UTILS_DIR)/utils.c \
                $(UTILS_DIR)/memory.c \
                $(UTILS_DIR)/memory_utils.c

# Full paths to source and object files ************************************** #
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# External libraries ********************************************************* #
LIBFT = $(LIBFT_DIR)/libft.a
GC    = $(GC_DIR)/gc.a

# Compiler and flags ********************************************************* #
CC     = cc
CFLAGS = -Wall -Wextra -Werror -g3 \
		 -I$(INCLUDES_DIR) -I$(LIBFT_DIR)/includes -I$(GC_DIR)/includes

# Default rule *************************************************************** #
all: $(NAME)

# Build executable *********************************************************** #
$(NAME): $(OBJS) $(LIBFT) $(GC)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(GC) $(LIBFT) -o $(NAME) -lreadline
	@echo "Build complete."

# Build libft.a ************************************************************** #
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "libft built."

# Build gc.a ***************************************************************** #
$(GC): $(LIBFT)
	@echo "Building gc..."
	@$(MAKE) -s -C $(GC_DIR) LIBFT_PATH="../libft"
	@echo "gc built."

# Compile .c to .o with directory creation *********************************** #
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and libraries ******************************************* #
clean:
	@echo "Cleaning objects..."
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(GC_DIR) clean
	@echo "Clean done."

# Clean everything *********************************************************** #
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(GC_DIR) fclean

# Rebuild ******************************************************************** #
re: fclean all

# Phony targets ************************************************************** #
.PHONY: all clean fclean re
