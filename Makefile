NAME     = minishell
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g3 -fsanitize=address
LIBS     = -lreadline

OBJDIR   = obj
LIBFTDIR = libft

SOURCES = main.c \
          builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/unset.c \
          executor/exec_builtin.c executor/exec_external.c executor/executor.c executor/pipes.c executor/redir_handler.c \
          init/init_env.c init/init_shell.c \
          parser/expander.c parser/lexer.c parser/parser.c parser/quotes.c parser/redirections.c \
          signals/heredoc_signals.c signals/signals.c \
          utils/errors.c utils/ft_env_utils.c utils/ft_split_quotes.c utils/ft_strutils.c \
		  builtins/builtins.c parser/token_utils.c parser/parser_utils.c parser/utils.c parser/read_line.c

SRCS  = $(SOURCES)
OBJS  = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))
LIBFT = $(LIBFTDIR)/libft.a

# Targets
all: $(OBJDIR) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. -I$(LIBFTDIR) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re