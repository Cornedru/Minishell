/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:45:56 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 02:48:28 by ndehmej          ###   ########.fr       */
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

/* global ******************************************************************* */

extern volatile sig_atomic_t	g_signal;

/* prototypes *************************************************************** */

// System initialization
t_sys	*init_sys(char **envp);
int		read_line(t_sys *sys);

// Execution
int		execute(t_ast *node, t_sys *sys);

// Pipe handling
void	left_child(t_ast *node, t_sys *sys, int *pipe_fd);
void	right_child(t_ast *node, t_sys *sys, int *pipe_fd);
int		handle_pipe(t_ast *node, t_sys *sys);

// Builtin execution
int		execute_external(t_ast *node, t_sys *sys);
int		execute_builtin(t_ast *node, t_sys *sys);
int		is_builtin(char *cmd);

// Command execution
int		execute_forked_cmd(t_ast *node, t_sys *sys);
int		execute_cmd(t_ast *node, t_sys *sys);

// Environment handling
char	**env_getarray(t_env *envp);
char	*get_env_var(char *var_name, t_env *envp);
int		set_env_var(t_env **envp, char *var_name, char *content);
t_env	*pull_env(char **envp);

// Path handling
char	*pull_path(char **env_paths, char *cmd);
char	*find_cmd_path(t_sys *sys, char *cmd);

// Redirection handling
int		handle_redirection(t_ast *node, t_sys *sys);

// Built-ins
int		builtin_echo(t_ast *node);
int		builtin_pwd(void);
int		builtin_cd(t_ast *node, t_sys *sys);

// Environment utilities
char	**dup_array(char **array);
int		ft_envsize(t_env *envp);
t_env	*gc_envnew(char *var, char *content);
void	ft_envadd_back(t_env **lst, t_env *new);

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

// AST utilities
t_ast	*new_ast_node(t_ast_type type);
t_token	*advance_token(t_token **tokens);
int		count_word_tokens(t_token *start);

#endif