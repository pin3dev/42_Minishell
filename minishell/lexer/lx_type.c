/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:58:46 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 20:59:01 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_tokens_no_quotes(char *full_cmd, char **str2, int flag, int *s)
{
	int	c;
	int	heredoc_flag;

	c = 0;
	heredoc_flag = 0;
	while (full_cmd[c])
	{
		if (full_cmd[c] == 34 || full_cmd[c] == 39)
			c = c + split_quote(&full_cmd[c], str2, flag, s);
		if (full_cmd[c] == '|' || full_cmd[c] == '>' || full_cmd[c] == '<')
			split_pipes_n_redir(full_cmd, str2, &c, s);
		if (full_cmd[c] == ' ')
		{
			if (flag == 1)
				split_spaces(full_cmd, str2, &c, s);
			skip_spaces(full_cmd, &c);
		}
		if (full_cmd[c] != 34 && full_cmd[c] != 39 && full_cmd[c] != ' ' && \
		full_cmd[c] != '<' && full_cmd[c] != '>' && full_cmd[c] != '|' && \
		full_cmd[c] != '\0')
			c = c + copy_tokens(&full_cmd[c], str2, s, &heredoc_flag);
	}
}

void	split_tokens_w_quotes(char *full_cmd, char **str2, int c, int *s)
{
	int	count;
	int	heredoc_flag;

	heredoc_flag = 0;
	while (full_cmd[c])
	{
		if (full_cmd[c] == 34 || full_cmd[c] == 39)
			c = c + split_quote(&full_cmd[c], str2, 2, s);
		if (full_cmd[c] == '|' || full_cmd[c] == '>' || full_cmd[c] == '<')
			split_pipes_n_redir(full_cmd, str2, &c, s);
		if (full_cmd[c] == ' ')
			skip_spaces(full_cmd, &c);
		if (full_cmd[c] && full_cmd[c] != 34 && full_cmd[c] != 39 && \
		!token_type(full_cmd[c]))
		{
			count = count_rest_to_split(full_cmd, &c, 0);
			if (find_index(full_cmd, "/bheredoc/") != -1 && \
			find_index(full_cmd, "/bheredoc/") <= c && heredoc_flag == 0)
				heredoc_size(full_cmd, &count, &c, &heredoc_flag);
			str2[*s] = malloc(sizeof(char) * (count + 1));
			str2[*s][count] = '\0';
			str2[*s] = ft_strcpy2(str2[*s], &full_cmd[c - count], count);
			(*s)++;
		}
	}
}

char	**split_tokens(char *full_cmd, int flag)
{
	int		s;
	char	**str2; 

	s = count_tokens(full_cmd, flag);
	str2 = malloc(sizeof(char *) * (s + 1));
	if (!str2)
		return (NULL);
	s = 0;
	if (flag == 2)
		split_tokens_w_quotes(full_cmd, str2, 0, &s);
	else
		split_tokens_no_quotes(full_cmd, str2, flag, &s);
	str2[s] = NULL;
	return (str2);
}
