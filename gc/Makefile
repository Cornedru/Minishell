# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 03:00:00 by oligrien          #+#    #+#              #
#    Updated: 2025/06/27 00:13:35 by oligrien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories **************************************************************** #
SRCS_DIR = ./src
OBJS_DIR = ./obj

# Source Files *************************************************************** #
SRCS_FILES =	gc.c \
				gc_utils.c \
				gc_strdup.c \
				gc_strjoin.c \
				gc_split.c

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

NAME = gc.a

# Compilation **************************************************************** #
CC = cc
CFLAGS =  -Wall -Wextra -Werror -g3 -I./includes -I$(LIBFT_PATH)/includes

# Rules ********************************************************************** #
all: $(NAME)

# Compile .c files to .o files *********************************************** #
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@


# Build Library ************************************************************** #
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

# Clean ********************************************************************** #
clean:
	@rm -rf $(OBJS_DIR)

fclean: clean 
	@rm -f $(NAME)

re: fclean all

# **************************************************************************** #
.PHONY: all clean fclean  re