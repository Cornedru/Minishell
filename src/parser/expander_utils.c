#include "minishell.h"

t_token	*split_expanded_token(char *expanded, t_token_type type)
{
	char	**split_values;
	t_token	*new_tokens;
	t_token	*current;
	t_token	*tmp;
	int		i;
	char	*clean;

	clean = expanded;
	i = 0;
	while (clean[i])
	{
		if (clean[i] == '\t' || clean[i] == '\n')
			clean[i] = ' ';
		i++;
	}
	split_values = ft_split(clean, ' ');
	if (!split_values || !split_values[0])
	{
		if (split_values)
			ft_free_split(split_values);
		return (NULL);
	}
	new_tokens = NULL;
	i = 0;
	while (split_values[i])
	{
		if (ft_strlen(split_values[i]) == 0)
		{
			i++;
			continue ;
		}
		tmp = malloc(sizeof(t_token));
		if (!tmp)
			break ;
		tmp->type = type;
		tmp->value = ft_strdup(split_values[i]);
		tmp->next = NULL;
		if (!new_tokens)
			new_tokens = tmp;
		else
		{
			current = new_tokens;
			while (current->next)
				current = current->next;
			current->next = tmp;
		}
		i++;
	}
	ft_free_split(split_values);
	return (new_tokens);
}

char	*expand_token_segments(char *str, t_shell *shell)
{
	char	*result;
	char	*segment_result;
	int		i;
	int		start;
	char	quote;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			start = i + 1;
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
			{
				if (quote == '\'')
				{
					segment_result = ft_substr(str, start, i - start);
				}
				else
				{
					segment_result = expand_in_double_quotes(str, start, i,
							shell);
				}
				result = join_and_free(result, segment_result);
				i++;
			}
			else
			{
				segment_result = ft_substr(str, start - 1, i - start + 1);
				result = join_and_free(result, segment_result);
			}
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			segment_result = expand_outside_quotes(str, start, i, shell);
			result = join_and_free(result, segment_result);
		}
	}
	return (result);
}

char	*expand_outside_quotes(char *str, int start, int end, t_shell *shell)
{
	char	*result;
	char	*temp;
	char	*var_value;
	int		i;
	int		seg_start;

	result = ft_strdup("");
	i = start;
	while (i < end)
	{
		seg_start = i;
		while (i < end && str[i] != '$')
			i++;
		if (i > seg_start)
		{
			temp = ft_substr(str, seg_start, i - seg_start);
			result = join_and_free(result, temp);
		}
		if (i < end && str[i] == '$')
		{
			var_value = expand_variable(str, &i, shell);
			result = join_and_free(result, var_value);
		}
	}
	return (result);
}

char	*expand_variable(char *str, int *i, t_shell *shell)
{
	char	*result;
	int		start;

	result = expand_special_var(str, i, shell);
	if (result)
		return (result);
	start = *i + 1;
	if (!str[start] || (!ft_isalpha(str[start]) && str[start] != '_'
			&& !ft_isdigit(str[start])))
	{
		*i = start;
		return (ft_strdup("$"));
	}
	if (ft_isdigit(str[start]))
		return (handle_numeric_var(str, i, start));
	return (process_regular_var(str, i, start, shell));
}

char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}
