/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_tok_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:02:52 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 21:03:04 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	count_quote_token(char *str, int flag, int *i, int *tokens)
{
	char	quote;
	int		count;

	count = 0;
	quote = str[*i];
	(*i)++;
	if (flag == 2)
		count = 2;
	while (str[*i] != quote)
	{
		(*i)++;
		count++;
	}
	(*i)++;
	if (count > 0)
		(*tokens)++;
}

void	count_special_tokens(char *str, int flag, int *i, int *tokens)
{
	if (str[*i] == ' ')
	{
		if (flag == 1)
			(*tokens)++;
		while (str[*i] == ' ')
			(*i)++;
	}
	if (str[*i] == '|')
	{
		(*tokens)++;
		(*i)++;
	}
	if (str[*i] == '>' || str[*i] == '<')
	{
		(*tokens)++;
		(*i)++;
		if (str[*i] == str[(*i) - 1])
			(*i)++;
	}
}

void	count_rest_tokens(char *str, int *i, int *tokens, int *heredoc)
{
	int	index;

	(*tokens)++;
	index = find_index(str, "/bheredoc/");
	while (str[*i] != 34 && str[*i] != 39 && str[*i] != ' ' && \
	str[*i] != '|' && str[*i] != '>' && str[*i] != '<' && str[*i] != '\0')
		(*i)++;
	if (index != -1 && index <= *i && *heredoc == 0)
	{
		*i = find_index(str, "/eheredoc/");
		*heredoc = 1;
		if (str[*i] == 34 || str[*i] == 39)
			(*i)++;
	}
}

int	count_tokens(char *str, int flag)
{
	int	tokens;
	int	i;
	int	heredoc;

	tokens = 0;
	i = 0;
	heredoc = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39))
			count_quote_token(str, flag, &i, &tokens);
		if (str[i] == ' ' || str[i] == '|' || str[i] == '>' || str[i] == '<')
			count_special_tokens(str, flag, &i, &tokens);
		if (str[i] != 34 && str[i] != 39 && str[i] != ' ' && str[i] != '|' && \
		str[i] != '>' && str[i] != '<' && str[i] != '\0')
			count_rest_tokens(str, &i, &tokens, &heredoc);
	}
	return (tokens);
}
