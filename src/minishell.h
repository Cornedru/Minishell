/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/24 04:32:58 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
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

// volatile sig_atomic_t	g_signal_status;

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

typedef struct s_ast
{
	t_ast_type		type;
	char			**argv;
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
t_token		*lexer(char *input);
t_ast		*parse(t_token **tokens);
void		free_tokens(t_token *tokens);
void		free_ast(t_ast *ast);
void		expand_tokens(t_token *tokens, t_shell *shell);
int			check_quotes(char *line);

/* Executor functions */
int			execute_command(t_ast *ast, t_shell *shell);
int			execute_pipeline(t_ast *ast, t_shell *shell);

/* Signal functions */
int			check_signal_status(void);

/* Builtin functions */
int			is_builtin(char *cmd);
int			builtin_echo(char **argv);
int			builtin_cd(char **argv, t_shell *shell);
int			builtin_pwd(void);
int			builtin_export(char **argv, t_shell *shell);
int			builtin_unset(char **argv, t_shell *shell);
int			builtin_env(t_shell *shell);
int			builtin_exit(char **argv, t_shell *shell);
char		*get_oldpwd_path(t_shell *shell);

/* Environment functions */
char		*get_env_value(char *key, t_shell *shell);
void		set_env_value(char *key, char *value, t_shell *shell);

/* Utils */
void		cleanup_shell(t_shell *shell);
int			is_numeric(char *str);
void		print_exported_vars(t_shell *shell);
void		mark_as_exported(char *key, t_shell *shell);
int			is_valid_identifier(char *str);

#endif