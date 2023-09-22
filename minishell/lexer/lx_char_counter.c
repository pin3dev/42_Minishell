/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_char_counter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:12:18 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 21:12:32 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_quote_to_split(char *full_cmd, int c)
{
	int		count;
	char	quote;

	count = 0;
	quote = full_cmd[0];
	while (full_cmd[c] && full_cmd[c] != quote)
	{
		count++;
		c++;
	}
	return (count);
}

int	count_rest_to_split(char *full_cmd, int *c, int count)
{
	while (full_cmd[*c] != 34 && full_cmd[*c] != 39 && full_cmd[*c] != ' ' && \
	full_cmd[*c] != '<' && full_cmd[*c] != '>' && full_cmd[*c] != '|' && \
	full_cmd[*c] != '\0')
	{
		count++;
		(*c)++;
	}
	return (count);
}

void	heredoc_size(char *full_cmd, int *count, int *c, int *heredoc_flag)
{
	*heredoc_flag = 1;
	while (find_index(full_cmd, "/eheredoc/") > *c)
	{
		(*count)++;
		(*c)++;
	}
}
