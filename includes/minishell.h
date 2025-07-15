// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   minishell.h                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/28 21:45:56 by oligrien          #+#    #+#             */
// /*   Updated: 2025/07/15 01:24:34 by ndehmej          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef MINISHELL_H
// # define MINISHELL_H

// /* includes ***************************************************************** */

// # include <errno.h>
// # include <fcntl.h>
// # include <signal.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <string.h>
// # include <sys/types.h>
// # include <sys/wait.h>
// # include <unistd.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// # include "../libft/includes/libft.h"
// # include "../gc/includes/gc.h"

// # define PROMPT "minishell$ "
// # define SIG_NONE 0
// # define SIG_INTERRUPT 1
// # define SIG_QUIT 2
// # define SIG_EOF 3

// /* typedef ****************************************************************** */

// // TOKEN ------------------------------

// typedef enum e_token_type
// {
// 	TOKEN_WORD,
// 	TOKEN_PIPE,			// |
// 	TOKEN_REDIR_IN,		// <
// 	TOKEN_REDIR_OUT,	// >
// 	TOKEN_REDIR_APPEND,	// >>
// 	TOKEN_HEREDOC,		// <<
// 	TOKEN_AND,			// &&
// 	TOKEN_OR,			// ||
// 	TOKEN_INVALID,
// 	TOKEN_EOF			// EOF
// }								t_token_type;

// typedef struct s_token
// {
// 	t_token_type				type;
// 	char						*value;
// 	struct s_token				*next;
// }								t_token;

// // AST --------------------------------

// typedef enum e_ast_type
// {
// 	AST_CMD,
// 	AST_PIPE,			// |
// 	AST_REDIR_IN,		// <
// 	AST_REDIR_OUT,		// >
// 	AST_REDIR_APPEND,	// >>
// 	AST_HEREDOC,		// <<
// 	AST_AND,			// &&
// 	AST_OR				// ||
// }								t_ast_type;

// typedef struct s_ast
// {
// 	t_ast_type					type;
// 	char						**args;			// Arguments for commands
// 	char						*filename;		// Filename for redirections
// 	struct s_ast				*left;
// 	struct s_ast				*right;
// }								t_ast;

// // REDIR (if needed) ------------------

// typedef struct s_redir
// {
// 	t_token_type				type;
// 	char						*file;
// 	struct s_redir				*next;
// }								t_redir;

// // SYS --------------------------------

// typedef struct s_env
// {
// 	char						*var;
// 	char						*content;
// 	struct s_env				*next;
// 	struct s_env				*prev;
// }								t_env;

// typedef struct s_sys
// {
// 	t_token						*token;
// 	t_ast						*ast;
// 	t_env						*env_lst;
// 	char						**envp;
// 	int							exit_status;
// 	int							exit;
// }								t_sys;

// typedef struct s_expand_params
// {
// 	int		start;
// 	int		end;
// 	char	quote;
// }			t_expand_params;

// /* global ******************************************************************* */

// extern volatile sig_atomic_t	g_signal;

// /* prototypes *************************************************************** */

// // System initialization
// t_sys	*init_sys(char **envp);
// int		read_line(t_sys *sys);

// // Execution
// int		execute(t_ast *node, t_sys *sys);

// // Pipe handling
// void	left_child(t_ast *node, t_sys *sys, int *pipe_fd);
// void	right_child(t_ast *node, t_sys *sys, int *pipe_fd);
// int		handle_pipe(t_ast *node, t_sys *sys);

// // Builtin execution
// int		execute_external(t_ast *node, t_sys *sys);
// int		execute_builtin(t_ast *node, t_sys *sys);
// int		is_builtin(char *cmd);

// // Command execution
// int		execute_forked_cmd(t_ast *node, t_sys *sys);
// int		execute_cmd(t_ast *node, t_sys *sys);

// // Environment handling
// char	**env_getarray(t_env *envp);
// char	*get_env_var(char *var_name, t_env *envp);
// // int		set_env_var(t_env **envp, char *var_name, char *content);
// t_env	*pull_env(char **envp);
// int		set_env_var(t_sys *sys, t_env **envp, char *var_name, char *content);

// // Path handling
// char	*pull_path(char **env_paths, char *cmd);
// char	*find_cmd_path(t_sys *sys, char *cmd);

// // Redirection handling
// int		handle_redirection(t_ast *node, t_sys *sys);

// // Built-ins
// int		builtin_cd(t_ast *node, t_sys *sys);
// int		builtin_echo(t_ast *node);
// int		builtin_env(t_sys *sys);
// int		builtin_exit(t_ast *node, t_sys *sys);
// int		builtin_export(t_ast *node, t_sys *sys);
// int		builtin_pwd(void);
// int		builtin_unset(t_ast *node, t_sys *sys);

// // Environment utilities
// char	**dup_array(char **array);
// int		ft_envsize(t_env *envp);
// t_env	*gc_envnew(char *var, char *content);
// void	ft_envadd_back(t_env **lst, t_env *new);

// // Parser functions
// t_token	*lexer(char *input);
// t_ast	*parse(t_token **tokens);
// void	free_tokens(t_token *tokens);
// void	free_ast(t_ast *ast);
// void	expand_tokens(t_token *tokens, t_sys *sys);
// int		check_quotes(char *line);
// char	*remove_quotes(char *str);

// // Parser helper functions
// t_ast	*parse_pipeline(t_token **tokens);
// t_ast	*parse_and_or(t_token **tokens);
// t_ast	*create_pipeline_node(t_ast *left, t_ast *right);
// t_ast	*create_and_or_node(t_ast *left, t_ast *right, t_ast_type type);
// t_ast	*parse_command(t_token **tokens);
// t_ast	*parse_simple_command(t_token **tokens);
// char	**parse_args(t_token **tokens);


// // Lexer utilities
// int		is_operator(char c);
// int		skip_whitespace(char *input, int i);
// t_token_type	get_operator_type(char *input, int i);
// int		get_operator_len(char *input, int i);
// t_token	*create_token(t_token_type type, char *value);
// void	add_token(t_token **tokens, t_token *new_token);
// int		extract_word_with_quotes(char *input, int i, char **word);
// int		extract_operator(char *input, int i, char **op);

// // Expansion utilities
// char	*expand_variable(char *str, int *i, t_sys *sys);
// char	*expand_special_var(char *str, int *i, t_sys *sys);
// char	*expand_token_value(char *str, t_sys *sys);
// char	*expand_outside_quotes(char *str, int start, int end, t_sys *sys);
// char	*expand_segment(char *str, int start, int end, t_sys *sys);
// char	*expand_in_double_quotes(char *str, int start, int end, t_sys *sys);
// char	*expand_regular_var(char *str, int *i, t_sys *sys);
// char	*handle_digit_var(char *str, int *i, char *key, char *value);
// char	*extract_var_key(char *str, int start, int *end);
// char	*get_var_value(char *key, t_sys *sys, int *i, int end);
// char	*handle_numeric_var(char *str, int *i, int start);
// char	*expand_token_segments(char *str, t_sys *sys);
// char	*process_regular_var(char *str, int *i, int start, t_sys *sys);
// char	*normalize_whitespace(char *expanded);

// // Quote handling utilities
// void	handle_single_quote(char *str, int *i, char **result);
// void	handle_double_quote(char *str, int *i, t_sys *sys, char **result);
// void	handle_quoted_segment(char *str, int *i, t_sys *sys, char **result);
// void	process_quote(char *str, int *i, char **result, char quote);
// void		copy_quoted_content(char *str, int *i, int *j, char *result);
// int		count_quoted_chars(char *str, int *i);
// int		get_unquoted_length(char *str);

// // Token utilities
// t_token	*alloc_token_node(char *value, t_token_type type);
// void	append_token(t_token **head, t_token *new_token);
// t_token	*create_token_list(char **split_values, t_token_type type);
// t_token	*split_expanded_token(char *expanded, t_token_type type);
// void	replace_token_value(t_token *current, t_token *split_tokens);

// // Utility functions
// char	*join_and_free(char *s1, char *s2);
// char	**gather_all_words(t_token **tokens);
// int		has_quotes(char *str);
// int		has_whitespace(char *str);
// int		should_split_token(char *original, char *expanded);
// void	ft_clear(void);

// // AST utilities
// t_ast	*new_ast_node(t_ast_type type);
// t_token	*advance_token(t_token **tokens);
// int		count_word_tokens(t_token *start);

// // Heredoc
// int		handle_heredoc(char *delimiter);

// // Redirections (if t_redir is used)
// t_redir	*parse_redir(t_token **tokens);
// void	add_redir(t_redir **redirs, t_redir *new_redir);

// // Mock functions for testing (remove in production)
// t_ast	*mock_ls_command(void);
// t_ast	*mock_redir_command(void);
// t_ast	*mock_pipe_command(void);


// void	handle_quote_section(char *str, int *i, char **result, t_sys *sys);
// char	*process_segment(char *str, int *i, int seg_start, t_sys *sys);
// char	*handle_invalid_or_numeric_var(char *str, int *i);
// char	*extract_env_value(char *str, int *i, int start, t_sys *sys);
// char	*expand_quoted_content(char *str, int start, int end, t_sys *sys);
// char	*expand_in_quotes(char *str, t_expand_params *params, t_sys *sys);
// int		are_quotes_closed(const char *str);
// char	**create_empty_argv(void);
// int		init_command_node(t_ast **node);
// int		skip_valid_redirections(t_token **tokens);
// int		is_invalid_pipe(t_token **tokens);
// t_ast	*handle_pipeline_right(t_ast *left, t_token **tokens);
// t_ast	*parse_single_redirection(t_token **tokens);
// int		is_redirection_token(t_token_type type);
// t_ast	*parse_redirections(t_token **tokens);
// t_ast	*parse_line(char *line, t_sys *sys);
// /* Prototypes à ajouter dans minishell.h */

// // Parser helper functions
// int		parse_remaining_tokens(t_token **tokens, t_ast **cmd);
// int		count_consecutive_words(t_token *tokens);

// // Syntax validation
// int		is_operator_token(t_token_type type);
// int		validate_syntax(t_token *tokens);

// // Test functions
// void	print_ast_tree(t_ast *node, int depth);
// void	test_echo_redirect_args(void);
// void	test_parsing_edge_cases(void);
// void	test_parsing_errors(void);
// void	run_parsing_tests(void);
// void	run_all_parsing_tests(void);
// void	free_envnode(t_env *env_lst);
// char	**env_getarray(t_env *env_lst);
// int		update_env_array(t_sys *sys);
// #endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:45:56 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/08 19:58:04 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* includes ***************************************************************** */

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"
# include "../gc/includes/gc.h"

# define PROMPT "minishell$ "
# define SIG_NONE 0
# define SIG_INTERRUPT 1
# define SIG_QUIT 2
# define SIG_EOF 3

/* typedef ****************************************************************** */

// TOKEN ------------------------------

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,			// |
	TOKEN_REDIR_IN,		// <
	TOKEN_REDIR_OUT,	// >
	TOKEN_REDIR_APPEND,	// >>
	TOKEN_HEREDOC,		// <<
	TOKEN_AND,			// &&
	TOKEN_OR,			// ||
	TOKEN_INVALID,
	TOKEN_EOF			// EOF
}								t_token_type;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}								t_token;

// AST --------------------------------

typedef enum e_ast_type
{
	AST_CMD,
	AST_WORD,
	AST_PIPE,			// |
	AST_REDIR_IN,		// <
	AST_REDIR_OUT,		// >
	AST_REDIR_APPEND,	// >>
	AST_HEREDOC,		// <<
	AST_AND,			// &&
	AST_OR				// ||
}								t_ast_type;

typedef struct s_ast
{
	t_ast_type					type;
	char						*word;
	char						**args;			// Arguments for commands
	char						*filename;		// Filename for redirections
	struct s_ast				*left;
	struct s_ast				*right;
}								t_ast;

// REDIR (if needed) ------------------

typedef struct s_redir
{
	t_token_type				type;
	char						*file;
	struct s_redir				*next;
}								t_redir;

// SYS --------------------------------

typedef struct s_env
{
	char						*var;
	char						*content;
	struct s_env				*next;
	struct s_env				*prev;
}								t_env;

typedef struct s_sys
{
	t_token						*token;
	t_ast						*ast;
	t_env						*env_lst;
	char						**envp;
	int							exit_status;
	int							exit;
}								t_sys;

typedef struct s_expand_params
{
	int		start;
	int		end;
	char	quote;
}			t_expand_params;

/* global ******************************************************************* */

extern volatile sig_atomic_t	g_signal;

/* prototypes *************************************************************** */

// System initialization
t_sys	*init_sys(char **envp);
// int		read_line(t_sys *sys);

// init.c -----------------------------

t_env	*pull_env(char **envp);
int		init_syse(t_sys **sys, char **envp);
int		init_shell(t_sys **sys, char **envp);



// exec.c -----------------------------

int		execute(t_ast *node, t_sys *sys);
int		read_line(t_sys *sys);



// exec_cmd.c -------------------------

int		execute_builtin(t_ast *node, t_sys *sys);
int		is_builtin(char *cmd);
int		execute_external(t_ast *node, t_sys *sys);
int		execute_forked_cmd(t_ast *node, t_sys *sys);
int		execute_cmd(t_ast *node, t_sys *sys);



// pipe.c -----------------------------

int		handle_pipe(t_ast *node, t_sys *sys);



// env_lst.c ------------------------------

int		is_valid_identifier(char *arg);
int		unset_env_var(t_sys *sys, t_env **env_lst, char *var_name);
int		set_env_var(t_sys *sys, t_env **envp, char *var_name, char *content);
char	*get_env_var(char *var_name, t_env *env_lst);

// env_array.c

char	**dup_array(char **array);
char	**env_getarray(t_env *env_lst);
int		update_env_array(t_sys *sys);

// 	env_utils.c	-----------------------

void	free_envnode(t_env *env_lst);
int		ft_envsize(t_env *env_lst);
t_env	*gc_envnew(char *var, char *content);
void	ft_envadd_back(t_env **env_lst, t_env *new);



// path.c -----------------------------

char	*find_cmd_path(t_sys *sys, char *cmd);



// redir.c ----------------------------

int		handle_redirection(t_ast *node, t_sys *sys);



// built-ins --------------------------

int		builtin_cd(t_ast *node, t_sys *sys);
int		builtin_echo(t_ast *node);
int		builtin_env(t_sys *sys);
int		builtin_exit(t_ast *node, t_sys *sys);
int		builtin_export(t_ast *node, t_sys *sys);
int		builtin_pwd(void);
int		builtin_unset(t_ast *node, t_sys *sys);

// Parser functions
t_token	*lexer(char *input);
t_ast	*parse(t_token **tokens);
void	free_tokens(t_token *tokens);
void	free_ast(t_ast *ast);
void	expand_tokens(t_token *tokens, t_sys *sys);
int		check_quotes(char *line);
char	*remove_quotes(char *str);

// Parser helper functions
t_ast	*parse_pipeline(t_token **tokens);
t_ast	*parse_and_or(t_token **tokens);
t_ast	*create_pipeline_node(t_ast *left, t_ast *right);
t_ast	*create_and_or_node(t_ast *left, t_ast *right, t_ast_type type);
t_ast	*parse_command(t_token **tokens);
t_ast	*parse_simple_command(t_token **tokens);
char	**parse_args(t_token **tokens);


// Lexer utilities
int		is_operator(char c);
int		skip_whitespace(char *input, int i);
t_token_type	get_operator_type(char *input, int i);
int		get_operator_len(char *input, int i);
t_token	*create_token(t_token_type type, char *value);
void	add_token(t_token **tokens, t_token *new_token);
int		extract_word_with_quotes(char *input, int i, char **word);
int		extract_operator(char *input, int i, char **op);

// Expansion utilities
char	*expand_variable(char *str, int *i, t_sys *sys);
char	*expand_special_var(char *str, int *i, t_sys *sys);
char	*expand_token_value(char *str, t_sys *sys);
char	*expand_outside_quotes(char *str, int start, int end, t_sys *sys);
char	*expand_segment(char *str, int start, int end, t_sys *sys);
char	*expand_in_double_quotes(char *str, int start, int end, t_sys *sys);
char	*expand_regular_var(char *str, int *i, t_sys *sys);
char	*handle_digit_var(char *str, int *i, char *key, char *value);
char	*extract_var_key(char *str, int start, int *end);
char	*get_var_value(char *key, t_sys *sys, int *i, int end);
char	*handle_numeric_var(char *str, int *i, int start);
char	*expand_token_segments(char *str, t_sys *sys);
char	*process_regular_var(char *str, int *i, int start, t_sys *sys);
char	*normalize_whitespace(char *expanded);

// Quote handling utilities
void	handle_single_quote(char *str, int *i, char **result);
void	handle_double_quote(char *str, int *i, t_sys *sys, char **result);
void	handle_quoted_segment(char *str, int *i, t_sys *sys, char **result);
void	process_quote(char *str, int *i, char **result, char quote);
void		copy_quoted_content(char *str, int *i, int *j, char *result);
int		count_quoted_chars(char *str, int *i);
int		get_unquoted_length(char *str);

// Token utilities
t_token	*alloc_token_node(char *value, t_token_type type);
void	append_token(t_token **head, t_token *new_token);
t_token	*create_token_list(char **split_values, t_token_type type);
t_token	*split_expanded_token(char *expanded, t_token_type type);
void	replace_token_value(t_token *current, t_token *split_tokens);

// Utility functions
char	*join_and_free(char *s1, char *s2);
char	**gather_all_words(t_token **tokens);
int		has_quotes(char *str);
int		has_whitespace(char *str);
int		should_split_token(char *original, char *expanded);
void	ft_clear(void);

// AST utilities
t_ast	*new_ast_node(t_ast_type type);
t_token	*advance_token(t_token **tokens);
int		count_word_tokens(t_token *start);

// Heredoc
int		handle_heredoc(char *delimiter);

// Redirections (if t_redir is used)
t_redir	*redir(t_token **tokens);
void	add_redir(t_redir **redirs, t_redir *new_redir);

// Mock functions for testing (remove in production)
t_ast	*mock_ls_command(void);
t_ast	*mock_redir_command(void);
t_ast	*mock_pipe_command(void);


void	handle_quote_section(char *str, int *i, char **result, t_sys *sys);
char	*process_segment(char *str, int *i, int seg_start, t_sys *sys);
char	*handle_invalid_or_numeric_var(char *str, int *i);
char	*extract_env_value(char *str, int *i, int start, t_sys *sys);
char	*expand_quoted_content(char *str, int start, int end, t_sys *sys);
char	*expand_in_quotes(char *str, t_expand_params *params, t_sys *sys);
int		are_quotes_closed(const char *str);
char	**create_empty_argv(void);
int		init_command_node(t_ast **node);
int		skip_valid_redirections(t_token **tokens);
int		is_invalid_pipe(t_token **tokens);
t_ast	*handle_pipeline_right(t_ast *left, t_token **tokens);
t_ast	*parse_single_redirection(t_token **tokens);
int		is_redirection_token(t_token_type type);
t_ast	*parse_redirections(t_token **tokens);
t_ast	*parse_line(char *line, t_sys *sys);
// int		execute_builtin(t_ast *node, t_sys *sys);
// int		builtin_env(t_sys *sys);
// int		builtin_exit(t_ast *node, t_sys *sys);
// int		builtin_export(t_ast *node, t_sys *sys);
// int 	builtin_unset(t_ast *node, t_sys *sys);
// char	**dup_array(char **array);
long long int	ft_atoll(const char *nptr, int *fail);

int	parse_remaining_tokens(t_token **tokens, t_ast **cmd);
t_ast	*attach_redirections(t_ast *cmd, t_ast *redir);
int	validate_syntax(t_token *tokens);
int	is_operator_token(t_token_type type);
int	check_operator_syntax(t_token *curr, t_token *prev);
 int	check_redirection_syntax(t_token *curr);
char	**merge_args(char **old_args, char **new_args);
t_ast	*collect_redirections_and_args(t_token **tokens, t_ast **cmd);

#endif