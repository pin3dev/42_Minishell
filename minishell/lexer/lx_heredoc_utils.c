/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_heredoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:52:09 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 16:52:11 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*concatenate_string(char *s1, char *s2)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	ft_strcpy(new_line, s1);
	while (s2[i])
	{
		new_line[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	new_line[i + ft_strlen(s1)] = '\0';
	free(s1);
	free(s2);
	return (new_line);
}

char	*find_delimiter(char *input)
{
	char	**tokens;
	char	*delimiter;
	int		i;

	i = 0;
	delimiter = NULL;
	tokens = split_tokens(input, 2);
	while (tokens[i] && ft_strcmp(tokens[i], "<<"))
		i++;
	if (tokens[i])
		delimiter = ft_strdup(tokens[i + 1]);
	free_array(tokens, true);
	return (delimiter);
}

int	verify_heredoc(char *input, t_global *global, int i, int exit)
{
	char	*delimiter;

	delimiter = find_delimiter(input);
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			write (1, "> ", 2);
			exit = heredoc(input, i, global, delimiter);
			break ;
		}
		i++;
	}
	if (!input[i])
		global->line = input;
	free(delimiter);
	return (exit);
}

int	find_index(char *str, char *word)
{
	int	str_len;
	int	word_len;
	int	i;
	int	j;

	str_len = ft_strlen(str);
	word_len = ft_strlen(word);
	i = 0;
	while (i <= str_len - word_len) 
	{
		j = 0;
		while (j < word_len && str[i + j] == word[j]) 
			j++;
		if (j == word_len) 
			return (i + j);
		i++;
	}
	return (-1); 
}
