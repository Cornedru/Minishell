#include "minishell.h"

static char	*get_env_value(char *key, t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*expand_variable(char *str, int *i, t_shell *shell)
{
	int		end;
	char	*key;
	char	*value;

	int start = *i + 1; /* Skip '$' */
	end = start;
	/* Handle special cases */
	if (str[start] == '?')
	{
		*i = start + 1;
		return (ft_itoa(shell->last_status));
	}
	if (str[start] == '$')
	{
		*i = start + 1;
		return (ft_itoa(getpid()));
	}
	/* Regular variable name */
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	if (end == start) /* No variable name after $ */
	{
		*i = start;
		return (ft_strdup("$"));
	}
	key = ft_substr(str, start, end - start);
	if (!key)
		return (NULL);
	value = get_env_value(key, shell);
	*i = end;
	free(key);
	return (value ? ft_strdup(value) : ft_strdup(""));
}

static char	*expand_string(char *str, t_shell *shell)
{
	char	*result;
	char	*temp;
	char	*expanded;
	int		i;
	int		in_single_quotes;
	int		in_double_quotes;
			char c[2] = {str[i], '\0'};

	result = ft_strdup("");
	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			i++;
		}
		else if (str[i] == '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;
		}
		else if (str[i] == '$' && !in_single_quotes)
		{
			expanded = expand_variable(str, &i, shell);
			if (expanded)
			{
				temp = ft_strjoin(result, expanded);
				free(result);
				free(expanded);
				result = temp;
			}
		}
		else
		{
			temp = ft_strjoin(result, c);
			free(result);
			result = temp;
			i++;
		}
	}
	return (result);
}

void	expand_tokens(t_token *tokens, t_shell *shell)
{
	char *expanded;

	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			expanded = expand_string(tokens->value, shell);
			if (expanded)
			{
				free(tokens->value);
				tokens->value = expanded;
			}
		}
		tokens = tokens->next;
	}
}