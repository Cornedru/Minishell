/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/06 06:19:38 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**create_empty_args(void)
{
	char	**argv;

	argv = (char **)gc_malloc(sizeof(char *) * 2);
	if (argv)
	{
		argv[0] = gc_strdup("");
		argv[1] = NULL;
	}
	return (argv);
}

char	**parse_args(t_token **tokens)
{
	char	**argv;
	int		argc;
	int		i;

	argc = count_word_tokens(*tokens);
	if (argc == 0)
		return (create_empty_args());
	argv = (char **)gc_malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			argv[i] = remove_quotes((*tokens)->value);
			if (!argv[i])
				argv[i] = gc_strdup((*tokens)->value);
			i++;
		}
		advance_token(tokens);
	}
	argv[i] = NULL;
	return (argv);
}

t_ast	*parse(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_and_or(tokens));
}
