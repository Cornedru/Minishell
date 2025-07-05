/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:45:56 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/06 00:26:56 by oligrien         ###   ########.fr       */
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
	char						**args;			// Arguments for commands
	char						*filename;		// Filename for redirections
	struct s_ast				*left;
	struct s_ast				*right;
}								t_ast;

// SYS --------------------------------

typedef struct s_env
{
	char						*var;
	char						*content;
	struct s_env				*next;
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

/* global ******************************************************************* */
extern volatile sig_atomic_t	g_signal;

/* prototypes *************************************************************** */

// test.c -----------------------------

t_ast	*mock_ls_command(void);
t_ast	*mock_redir_in_command(void);
t_ast	*mock_pipe_command(void);
t_ast	*mock_export_command(void);
t_ast	*mock_export_no_args_command(void);
t_ast	*mock_unset_command(void);
t_ast	*mock_cd_command(void);
t_ast	*mock_env_command(void);
t_ast	*mock_exit_command(void);
t_ast	*mock_redir_out_command(void);
t_ast	*mock_heredoc_command(void);



// init.c -----------------------------

t_env	*pull_env(char **envp);
int		init_sys(t_sys **sys, char **envp);
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



// utils ------------------------------




/* ************************************************************************** */
/* ************************************************************************** */
/*                          NEED ADJUSTMENTS                                  */
/* ************************************************************************** */
/* ************************************************************************** */

// /* Parser functions */
// t_token			*lexer(char *input);
// t_ast			*parse(t_token **tokens);
// void			free_tokens(t_token *tokens);
// void			free_ast(t_ast *ast);
// void			expand_tokens(t_token *tokens, t_shell *shell);
// int				check_quotes(char *line);
// char			*remove_quotes(char *str);
// void			parse_redirections(t_token **tokens, t_ast *node);


// /* Parser helper functions */
// t_ast			*parse_pipeline(t_token **tokens);
// t_ast			*parse_and_or(t_token **tokens);
// t_ast			*create_pipeline_node(t_ast *left, t_ast *right);
// t_ast			*create_and_or_node(t_ast *left, t_ast *right, t_ast_type type);
// t_ast			*parse_command(t_token **tokens);
// t_ast			*parse_simple_command(t_token **tokens);


// /* Utils */
// void			cleanup_shell(t_shell *shell);
// int				is_numeric(char *str);
// void			print_exported_vars(t_shell *shell);
// void			mark_as_exported(char *key, t_shell *shell);
// int				is_valid_identifier(char *str);
// char			*ft_strjoin_free(char *s1, char *s2);
// void			free_env(t_env *env);
// void			free_redirs(t_redir *redirs);
// char			*ft_re(char *s, int old, int new);
// int				is_operator(char c);
// int				skip_whitespace(char *input, int i);
// t_token_type	get_operator_type(char *input, int i);
// int				get_operator_len(char *input, int i);
// t_token			*create_token(t_token_type type, char *value);
// void			add_token(t_token **tokens, t_token *new_token);
// int				extract_word_with_quotes(char *input, int i, char **word);
// int				extract_operator(char *input, int i, char **op);
// char			*expand_variable(char *str, int *i, t_shell *shell);
// char			*process_regular_var(char *str, int *i, int start,
// 					t_shell *shell);
// char			*handle_numeric_var(char *str, int *i, int start);
// char			*build_numeric_var_value(char *str, int *i, char *value);
// char			*expand_special_var(char *str, int *i, t_shell *shell);
// t_ast			*new_ast_node(t_ast_type type);
// t_token			*advance_token(t_token **tokens);
// t_redir			*parse_redir(t_token **tokens);
// void			add_redir(t_redir **redirs, t_redir *new_redir);
// char			**gather_all_words(t_token **tokens);
// void			ft_clear(void);
// int				should_split_token(char *original, char *expanded);
// t_token			*split_expanded_token(char *expanded, t_token_type type);
// char			*expand_token_segments(char *str, t_shell *shell);
// char			*expand_in_double_quotes(char *str, int start, int end,
// 					t_shell *shell);
// char			*expand_outside_quotes(char *str, int start, int end,
// 					t_shell *shell);
// char			*expand_regular_var(char *str, int *i, t_shell *shell);
// char			*join_and_free(char *s1, char *s2);
// void			handle_quoted_segment(char *str, int *i, t_shell *shell,
// 					char **result);
// int				count_word_tokens(t_token *start);
// char			**allocate_argv(int count);
// void			fill_argv(t_token **tokens, char **argv);
// char			*expand_segment(char *str, int start, int end, t_shell *shell);
// char			*handle_digit_var(char *str, int *i, char *key, char *value);
// char			*extract_var_key(char *str, int start, int *end);
// char			*get_var_value(char *key, t_shell *shell, int *i, int end);
// char			*normalize_whitespace(char *expanded);
// t_token			*alloc_token_node(char *value, t_token_type type);
// void			append_token(t_token **head, t_token *new_token);
// t_token			*create_token_list(char **split_values, t_token_type type);
// void			process_quote(char *str, int *i, char **result, char quote);
// void			handle_quoted_segment(char *str, int *i, t_shell *shell, char **result);
// int				has_whitespace(char *str);
// int				has_quotes(char *str);
// int				get_unquoted_length(char *str);
// int				count_quoted_chars(char *str, int *i);
// void			copy_quoted_content(char *str, int *i, int *j, char *result);
// void			replace_token_value(t_token *current, t_token *split_tokens);
// void			handle_quoted_segment(char *str, int *i, t_shell *shell, char **result);
// void			handle_single_quote(char *str, int *i, char **result);
// void			handle_double_quote(char *str, int *i, t_shell *shell,
// 					char **result);

#endif