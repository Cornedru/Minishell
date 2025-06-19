


#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>


// typedef enum e_node_type
// {
// 	NODE_CMD,
// 	NODE_PIPE,
// 	NODE_AND,
// 	NODE_OR,
// 	NODE_REDIR_IN,
// 	NODE_REDIR_OUT,
// 	NODE_REDIR_APPEND,
// 	NODE_HEREDOC,
// 	NODE_SUBSHELL,
// }	t_node_type;

// typedef struct s_ast
// {
// 	t_node_type			type;
// 	char				**args;		// pour NODE_CMD
// 	char				*file;		// pour redirections
// 	struct s_ast			*left;
// 	struct s_ast			*right;
// }	t_ast;

typedef enum e_token_type
{
	TOKEN_CMD,
	TOKEN_ARG,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,     // <
	TOKEN_REDIR_OUT,    // >
	TOKEN_REDIR_APPEND, // >>
	TOKEN_HEREDOC,       // <<
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_ERROR,
	TOKEN_FILE
}								t_token_type;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}
								t_token;
typedef struct s_shell
{
	int							last_exit_status;
	int							interactive;
	char						**env;
}								t_shell;

extern volatile sig_atomic_t	g_signal;
extern t_shell					g_shell;

t_token							*lexer(char *input);
t_token							*create_token(t_token_type type, char *value);
void							add_token(t_token **tokens, t_token *new_token);
void							free_tokens(t_token *tokens);
void							print_token_list(t_token *tokens);
const char						*get_token_type_name(t_token_type type);
t_token_type	get_operator_type(char *input, int i);
t_token_type	determine_word_type(char *word, t_token *tokens);
int	handle_quotes(char *input, int i, char quote);
int	skip_whitespace(char *input, int i);
int	is_operator(char c);
int	is_command_position(t_token *tokens);
int	is_builtin_command(char *word);

char	*read_complete_line(void);
char	*strjoin_free(char *s1, char *s2);
int	check_unmatched_quotes(const char *line);
// int skip_par(char *input, int i);

	
char							*ft_strdup(const char *s);
char							*ft_substr(char const *s, unsigned int start,
size_t len);
size_t							ft_strlen(const char *s);
int contains_error_token(t_token *tokens);
		
#endif

// typedef struct s_ast_node
// {
// 	t_ast_type					type;
// 	char **args;
// 	char *filename;
// 	struct s_ast_node			*left;
// 	struct s_ast_node			*right;
// 	int append_mode;
// }								t_ast_node;

// typedef enum e_ast_type
// {
// 	AST_COMMAND,
// 	AST_PIPE,
// 	AST_REDIRECT_IN,
// 	AST_REDIRECT_OUT,
// 	AST_REDIRECT_APPEND,
// 	AST_HEREDOC,
// 	AST_AND,
// 	AST_OR
// }								t_ast_type;


// #ifndef MINISHELL_H
// # define MINISHELL_H

// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <string.h>
// # include <fcntl.h>
// # include <sys/wait.h>
// # include <sys/stat.h>
// # include <signal.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// # include <errno.h>
// # include <dirent.h>
// # include <termios.h>
// # include <sys/ioctl.h>
// # include "libft/libft.h"

// # define PROMPT "minishell$ "
// # define MAX_PATH 1024

// extern volatile sig_atomic_t g_signal;

// typedef enum e_token_type {
// 	TOKEN_WORD,
// 	TOKEN_PIPE,
// 	TOKEN_REDIR_IN,
// 	TOKEN_REDIR_OUT,
// 	TOKEN_REDIR_APPEND,
// 	TOKEN_HEREDOC,
// 	TOKEN_EOF
// } t_token_type;

// typedef struct s_token {
// 	t_token_type	type;
// 	char			*value;
// 	struct s_token	*next;
// } t_token;

// typedef struct s_cmd {
// 	char			**args;
// 	char			*input_file; >
// 	char			*output_file; <
// 	int				append_mode; >>
// 	char			*heredoc_delim; <<
// 	int				heredoc_fd; 
// 	struct s_cmd	*next;
// } t_cmd;

// typedef struct s_shell {
// 	char	**envp;
// 	int		last_exit_status;
// 	t_cmd	*cmd_list;
// 	int		interactive;
// } t_shell;

// extern t_shell g_shell;

// t_token		*lexer(char *input);
// void		free_tokens(t_token *tokens);
// t_token		*create_token(t_token_type type, char *value);
// void		add_token(t_token **tokens, t_token *new_token);

// t_cmd		*parser(t_token *tokens);
// void		free_commands(t_cmd *cmd);
// t_cmd		*create_command(void);

// void		expand_variables(t_token *tokens);
// char		*expand_string(char *str);

// void		execute_commands(t_cmd *cmd);
// void		execute_single_command(t_cmd *cmd);
// char		*find_command_path(char *cmd);
// int			is_builtin(char *cmd);
// void		execute_builtin(t_cmd *cmd);

// void		execute_pipeline(t_cmd *cmd);
// void		setup_pipes(t_cmd *cmd, int **pipes, int cmd_count);
// void		close_pipes(int **pipes, int cmd_count);

// int			setup_redirections(t_cmd *cmd);
// int			handle_heredoc(char *delimiter);

// void		builtin_echo(t_cmd *cmd);
// void		builtin_cd(t_cmd *cmd);
// void		builtin_pwd(t_cmd *cmd);
// void		builtin_export(t_cmd *cmd);
// void		builtin_unset(t_cmd *cmd);
// void		builtin_env(t_cmd *cmd);
// void		builtin_exit(t_cmd *cmd);

// void		setup_signals(void);
// void		signal_handler(int sig);
// void		setup_child_signals(void);

// char		*ft_getenv(char *name);
// void		ft_setenv(char *name, char *value);
// void		ft_unsetenv(char *name);
// char		**copy_env(char **envp);
// void		free_env(char **env);
// int			ft_arraylen(char **array);
// void		print_error(char *cmd, char *arg, char *msg);
// char		*ft_strjoin_free(char *s1, char *s2);

// void		cleanup_shell(void);
// void		free_command(t_cmd *cmd);

// #endif

// t_ast_node						*ast_create_node(t_ast_type type);
// t_ast_node						*ast_create_command(char **args);
// t_ast_node						*ast_create_pipe(t_ast_node *left,
// 									t_ast_node *right);
// t_ast_node						*ast_create_redirect(t_ast_type type,
// t_ast_node *cmd, char *filename);
// t_ast_node						*parse_to_ast(t_token *tokens);
// void							ast_print(t_ast_node *node, int depth);
// void							ast_free(t_ast_node *node);