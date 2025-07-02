/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/02 21:43:54 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "minishell$ "
# define SIG_NONE 0
# define SIG_INTERRUPT 1
# define SIG_QUIT 2
# define SIG_EOF 3

extern volatile sig_atomic_t	g_signal_status;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_EOF
}	t_token_type;

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_PIPELINE,
	AST_AND,
	AST_OR,
	AST_SUBSHELL
}	t_ast_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast
{
	t_ast_type		type;
	char			**argv;
	t_redir			*redirs;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env			*env;
	int				last_status;
	int				interactive;
	char			*cwd;
}	t_shell;

/* Parser functions */
t_token			*lexer(char *input);
t_ast			*parse(t_token **tokens);
void			free_tokens(t_token *tokens);
void			free_ast(t_ast *ast);
void			expand_tokens(t_token *tokens, t_shell *shell);
int				check_quotes(char *line);
char			*remove_quotes(char *str);
void			parse_redirections(t_token **tokens, t_ast *node);


/* Parser helper functions */
t_ast			*parse_pipeline(t_token **tokens);
t_ast			*parse_and_or(t_token **tokens);
t_ast			*create_pipeline_node(t_ast *left, t_ast *right);
t_ast			*create_and_or_node(t_ast *left, t_ast *right, t_ast_type type);
t_ast			*parse_command(t_token **tokens);
t_ast			*parse_simple_command(t_token **tokens);




/* Executor functions */
int				execute_ast(t_ast *ast, t_shell *shell);
int				execute_command(t_ast *ast, t_shell *shell);
int				execute_pipeline(t_ast *ast, t_shell *shell);
int				execute_builtin(t_ast *node, t_shell *shell);
char			*find_command_path(char *cmd, t_shell *shell);
int				handle_heredoc(t_redir *redir);

/* Signal functions */
int				check_signal_status(void);
void			setup_signals(void);
void			setup_child_signals(void);

/* Builtin functions */
int				is_builtin(char *cmd);
int				builtin_echo(char **argv);
int				builtin_cd(char **argv, t_shell *shell);
int				builtin_pwd(void);
int				builtin_export(char **argv, t_shell *shell);
int				builtin_unset(char **argv, t_shell *shell);
int				builtin_env(t_shell *shell);
int				builtin_exit(char **argv, t_shell *shell);
char			*get_home_path(t_shell *shell);
char			*get_oldpwd_path(t_shell *shell);

/* Environment functions */
void			init_env(t_shell *shell);
char			*get_env_value(char *key, t_shell *shell);
void			set_env_value(char *key, char *value, t_shell *shell);
char			**env_to_array(t_env *env);

/* Utils */
void			cleanup_shell(t_shell *shell);
int				is_numeric(char *str);
void			print_exported_vars(t_shell *shell);
void			mark_as_exported(char *key, t_shell *shell);
int				is_valid_identifier(char *str);
char			*ft_strjoin_free(char *s1, char *s2);
void			free_env(t_env *env);
void			free_redirs(t_redir *redirs);
char			*ft_re(char *s, int old, int new);
int				is_operator(char c);
int				skip_whitespace(char *input, int i);
t_token_type	get_operator_type(char *input, int i);
int				get_operator_len(char *input, int i);
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **tokens, t_token *new_token);
int				extract_word_with_quotes(char *input, int i, char **word);
int				extract_operator(char *input, int i, char **op);
char			*expand_variable(char *str, int *i, t_shell *shell);
char			*process_regular_var(char *str, int *i, int start,
					t_shell *shell);
char			*handle_numeric_var(char *str, int *i, int start);
char			*build_numeric_var_value(char *str, int *i, char *value);
char			*expand_special_var(char *str, int *i, t_shell *shell);
t_ast			*new_ast_node(t_ast_type type);
t_token			*advance_token(t_token **tokens);
t_redir			*parse_redir(t_token **tokens);
void			add_redir(t_redir **redirs, t_redir *new_redir);
char			**gather_all_words(t_token **tokens);
void			ft_clear(void);
int				should_split_token(char *original, char *expanded);
t_token			*split_expanded_token(char *expanded, t_token_type type);
char			*expand_token_segments(char *str, t_shell *shell);
char			*expand_in_double_quotes(char *str, int start, int end,
					t_shell *shell);
char			*expand_outside_quotes(char *str, int start, int end,
					t_shell *shell);
char			*expand_regular_var(char *str, int *i, t_shell *shell);
char			*join_and_free(char *s1, char *s2);
void			handle_quoted_segment(char *str, int *i, t_shell *shell,
					char **result);
int				count_word_tokens(t_token *start);
char			**allocate_argv(int count);
void			fill_argv(t_token **tokens, char **argv);
char			*expand_segment(char *str, int start, int end, t_shell *shell);
char			*handle_digit_var(char *str, int *i, char *key, char *value);
char			*extract_var_key(char *str, int start, int *end);
char			*get_var_value(char *key, t_shell *shell, int *i, int end);
char			*normalize_whitespace(char *expanded);
t_token			*alloc_token_node(char *value, t_token_type type);
void			append_token(t_token **head, t_token *new_token);
t_token			*create_token_list(char **split_values, t_token_type type);
void			process_quote(char *str, int *i, char **result, char quote);
void			handle_quoted_segment(char *str, int *i, t_shell *shell, char **result);
int				has_whitespace(char *str);
int				has_quotes(char *str);
int				get_unquoted_length(char *str);
int				count_quoted_chars(char *str, int *i);
void			copy_quoted_content(char *str, int *i, int *j, char *result);
void			replace_token_value(t_token *current, t_token *split_tokens);
void			handle_quoted_segment(char *str, int *i, t_shell *shell, char **result);
void			handle_single_quote(char *str, int *i, char **result);
void			handle_double_quote(char *str, int *i, t_shell *shell,
					char **result);


#endif