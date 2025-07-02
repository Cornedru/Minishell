# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 03:00:00 by oligrien          #+#    #+#              #
#    Updated: 2025/07/02 22:17:36 by oligrien         ###   ########.fr        #
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

EXEC_DIR =		exec
BUILTINS_DIR = 	built-ins
UTILS_DIR =		utils
PRS_DIR =		parser

# Source Files *************************************************************** #
SRCS_FILES =	main.c \
				tests.c \
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
				$(PRS_DIR)/clear_utils.c \
				$(PRS_DIR)/clear_utils2.c \
				$(PRS_DIR)/parser_utils.c \
				$(PRS_DIR)/parser_utils2.c \
				$(PRS_DIR)/quotes.c \
				$(PRS_DIR)/utils2.c \
				$(UTILS_DIR)/utils.c \
				$(UTILS_DIR)/memory.c \
				$(UTILS_DIR)/memory_utils.c

SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

# libft ********************************************************************** #
LIBFT = $(LIBFT_DIR)/libft.a

# gc ************************************************************************* #
GC = $(GC_DIR)/gc.a

# Compilation **************************************************************** #
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I$(INCLUDES_DIR) -I$(LIBFT_DIR)/includes -I$(GC_DIR)/includes

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
	@mkdir -p $(OBJS_DIR)
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