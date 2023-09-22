/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:55:41 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 14:55:58 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	verify_redirections(char *input, int i)
{
	char	**split;

	split = split_tokens(input, 0);
	while (split[i])
	{
		if (redir_type(split[i]))
		{
			i++;
			if (!split[i])
			{
				print_error("syntax error near unexpected token `newline'", \
				NULL, NULL);
				return (set_new_status(2), false);
			}
			if (redir_type(split[i]) || !ft_strcmp(split[i], "|"))
			{
				print_error("syntax error near unexpected token", \
				split[i], NULL);
				return (set_new_status(2), false);
			}
		}
		i++;
	}
	free_array(split, true);
	return (true);
}

bool	verify_pipes(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (!input[i])
			{
				print_error("syntax error near unexpected token `newline'", \
				NULL, NULL);
				return (set_new_status(2), false);
			}
			if (input[i] == '|' )
			{
				printf("minixHell: syntax error near unexpected token `%c'\n", \
				input[i]);
				return (set_new_status(2), false);
			}
		}
		i++;
	}
	return (true);
}

int	verify_closed_quotes(char *input, char quote, int i)
{
	while (input[i]) 
	{
		if (input[i] == 34 || input[i] == 39) 
		{
			if (!quote || quote == input[i]) 
			{
				if (quote)
					quote = 0;
				else 
					quote = input[i];
			}
		}
		i++;
	}
	if (quote)
	{
		printf("minixHell: looking for matching `%c'\n", quote);
		return (set_new_status(2), false);
	}
	else
		return (true);
}

bool	verify_pipes_redir_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
	{
		i++;
		if (input[i] == '|')
			print_error("syntax error near unexpected token `||'", NULL, NULL);
		else
			print_error("syntax error near unexpected token `|'", NULL, NULL);
		set_new_status(2);
		return (false);
	}
	if (!verify_closed_quotes(input, 0, 0) || !verify_pipes(input, i) || \
	!verify_redirections(input, 0))
	{
		set_new_status(2);
		return (false);
	}
	return (true);
}

bool	verify_empty_str(char *str, int c)
{
	if (!str)
		return (1);
	while (str[c])
	{
		if (str[c] != ' ' && str[c] != '\0')
			return (0);
		c++;
	}
	return (1);
}
