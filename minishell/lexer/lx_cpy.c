/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_cpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:06:01 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 21:06:10 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_spaces(char *full_cmd, char **str, int *c, int *s)
{
	str[*s] = malloc(sizeof(char) * 2);
	str[*s][0] = full_cmd[*c];
	str[*s][1] = '\0';
	(*s)++;
}

int	split_quote(char *full_cmd, char **str, int flag, int *s)
{
	int	c;
	int	count;

	count = count_quote_to_split(full_cmd, 1);
	c = count;
	if (flag == 2)
		count = count + 2;
	if ((flag != 2 && count > 0) || (flag == 2 && count >= 2))
	{
		str[*s] = malloc(sizeof(char) * (count + 1));
		str[*s][count] = '\0';
		if (flag != 2)
		{
			full_cmd = full_cmd + 1;
			str[*s] = ft_strcpy2(str[*s], full_cmd, count);
		}
		else
			str[*s] = ft_strcpy2(str[*s], full_cmd, count);
		(*s)++;
	}
	return (c + 2);
}

void	split_pipes_n_redir(char *full_cmd, char **str, int *c, int *s)
{
	if (full_cmd[*c] == '|')
	{
		str[*s] = (char *)malloc(sizeof(char) * 2);
		str[*s][0] = '|';
		str[*s][1] = '\0';
	}
	else
	{
		if (full_cmd[(*c) + 1] == full_cmd[*c])
		{
			str[*s] = (char *)malloc(sizeof(char) * 3);
			str[*s] = ft_strcpy2(str[*s], &full_cmd[*c], 2);
			str[*s][2] = '\0';
			(*c)++;
		}
		else
		{
			str[*s] = (char *)malloc(sizeof(char) * 2);
			str[*s][0] = full_cmd[*c];
			str[*s][1] = '\0';
		}
	}
	(*s)++;
	(*c)++;
}

int	copy_tokens(char *full_cmd, char **str, int *s, int *heredoc_flag)
{
	int	c;
	int	index;

	c = 0;
	index = find_index(full_cmd, "/bheredoc/");
	while (full_cmd[c] && full_cmd[c] != 34 && full_cmd[c] != 39 && full_cmd[c] \
	!= ' ' && full_cmd[c] != '<' && full_cmd[c] != '>' && full_cmd[c] != '|')
		c++;
	if (index != -1 && index <= c && *heredoc_flag == 0)
	{
		*heredoc_flag = 1;
		while (find_index(full_cmd, "/eheredoc/") > c)
			c++;
		str[*s] = malloc(sizeof(char) * (c - 20 + 1));
		str[*s][c - 20] = '\0';
		str[*s] = ft_strcpy2(str[*s], &full_cmd[index], c - 20);
	}
	else
	{
		str[*s] = malloc(sizeof(char) * (c + 1));
		str[*s][c] = '\0';
		str[*s] = ft_strcpy2(str[*s], full_cmd, c);
	}
	(*s)++;
	return (c);
}
