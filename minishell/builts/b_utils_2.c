/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:04:08 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 13:08:02 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_quotes_aux(char *input, int index)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (i <= index) 
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
		return (0);
	else
		return (1);
}

int	token_type(char token)
{
	if (token == 32 || token == 9 || token == 11 || token == 13 || token == 10)
		return (SPACES);
	if (token == '|')
		return (PIPES);
	if (token == 34 || token == 39)
		return (QUOTES);
	if (token == '<' || token == '>')
		return (REDIRECTION);
	else
		return (0);
}
