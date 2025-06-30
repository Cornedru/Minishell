NAME     = minishell
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g3
LIBS     = -lreadline

OBJDIR   = obj
LIBFTDIR = libft
SRCDIR   = src

SOURCES = main.c \
		  $(SRCDIR)/builtins/builtin_handler.c \
		  $(SRCDIR)/builtins/cd.c \
		  $(SRCDIR)/builtins/cd_utils.c \
		  $(SRCDIR)/builtins/echo.c \
		  $(SRCDIR)/builtins/env.c \
		  $(SRCDIR)/builtins/exit.c \
		  $(SRCDIR)/builtins/export.c \
		  $(SRCDIR)/builtins/pwd.c \
		  $(SRCDIR)/builtins/unset.c \
		  $(SRCDIR)/env/env_manager.c \
		  $(SRCDIR)/env/env_utils.c \
		  $(SRCDIR)/executor/executor.c \
		  $(SRCDIR)/executor/pipes.c \
		  $(SRCDIR)/parser/expander.c \
		  $(SRCDIR)/parser/expander_utils.c \
		  $(SRCDIR)/parser/heredoc.c \
		  $(SRCDIR)/parser/lexer.c \
		  $(SRCDIR)/parser/lexer_utils.c \
		  $(SRCDIR)/parser/parser.c \
		  $(SRCDIR)/parser/clear_utils.c \
		  $(SRCDIR)/parser/parser_utils.c \
		  $(SRCDIR)/parser/quotes.c \
		  $(SRCDIR)/signals/signal_handler.c \
		  $(SRCDIR)/utils/utils.c \
		  $(SRCDIR)/utils/memory.c \
		  $(SRCDIR)/utils/memory_utils.c

OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SOURCES))
LIBFT = $(LIBFTDIR)/libft.a
INCLUDES = -I. -I$(LIBFTDIR) -I$(SRCDIR)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/$(SRCDIR)
	mkdir -p $(OBJDIR)/$(SRCDIR)/builtins
	mkdir -p $(OBJDIR)/$(SRCDIR)/env
	mkdir -p $(OBJDIR)/$(SRCDIR)/executor
	mkdir -p $(OBJDIR)/$(SRCDIR)/parser
	mkdir -p $(OBJDIR)/$(SRCDIR)/signals
	mkdir -p $(OBJDIR)/$(SRCDIR)/utils

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR) 2>/dev/null || true

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR) 2>/dev/null || true

re: fclean all

.PHONY: all clean fclean re

# # gc ************************************************************************* #
# GC = $(GC_DIR)/gc.a

# # Compilation **************************************************************** #
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -g3 -I$(INCLUDES_DIR) -I$(LIBFT_DIR)/includes -I$(GC_DIR)/includes



# # Build libft.a ************************************************************** #
# $(LIBFT):
# 	@echo "Making libft..."
# 	@$(MAKE) -s -C $(LIBFT_DIR)
# 	@echo "libft done."

# # Build gc.a ***************************************************************** #
# $(GC): $(LIBFT)
# 	@echo "Making gc..."
# 	@$(MAKE) -s -C $(GC_DIR) LIBFT_PATH="../libft"
# 	@echo "gc done."

# # Compile .c files to .o files *********************************************** #
# $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
# 	@mkdir -p $(OBJS_DIR)
# 	@$(CC) $(CFLAGS) -c $< -o $@
