/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_heredollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:28:49 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 21:28:58 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_dollar(t_global *global, char *dollar_line)
{
	int		index;
	int		mark;
	char	*line;
	char	*word;

	index = index_char(dollar_line, '$');
	mark = index;
	if (index != ft_strlen(dollar_line))
	{
		word = word_to_find(dollar_line, index, &mark, '\0');
		line = new_line(global, word, dollar_line, mark);
		free(word);
		free(dollar_line);
		dollar_line = ft_strdup(line);
		free(line);
	}
	return (dollar_line);
}

int	count_dollar(char *heredoc_line)
{
	int	i;
	int	count; 

	i = 0;
	count = 0;
	while (heredoc_line[i])
	{
		if (heredoc_line[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*heredoc_case(t_global *global, char *heredoc_l, char *full, int final)
{
	int		count;
	char	*line;
	char	*copy_line;

	count = count_dollar(heredoc_l);
	if (count != 0)
	{
		copy_line = ft_strdup(heredoc_l);
		while (count > 0)
		{
			copy_line = replace_dollar(global, copy_line);
			count--;
		}
		line = ft_strjoin(copy_line, &full[final]);
		free(copy_line);
		return (line);
	}
	else
		return (NULL);
}

char	*dollar_heredoc(t_global *global, char *heredoc_l, char *line, int *i)
{
	int		heredoc;
	int		final;
	char	*new_line;

	heredoc = find_index(line, "<<");
	new_line = ft_strdup_be(line, 0, heredoc - 1);
	final = find_index(line, heredoc_l);
	heredoc_l = heredoc_case(global, heredoc_l, line, final);
	if (heredoc_l)
	{
		free(line);
		line = concatenate_string(new_line, heredoc_l);
	}
	else
		free(new_line);
	(*i)++;
	return (line);
}
