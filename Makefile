NAME     = minishell
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g3
LIBS     = -lreadline

OBJDIR   = obj
LIBFTDIR = libft

SOURCES = main.c

OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SOURCES))
LIBFT = $(LIBFTDIR)/libft.a
INCLUDES = -I. -I$(LIBFTDIR)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

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
