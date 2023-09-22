/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_utils_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:32:47 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 21:32:56 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_word(char *prev_word)
{
	int		i;
	char	*word_to_find;

	i = 1;
	while (ft_isalnum(prev_word[i]) || prev_word[i] == 34 || prev_word[i] == 39)
		i++;
	i--;
	while (prev_word[i] == 34 || prev_word[i] == 39)
		i--;
	word_to_find = ft_strdup_be(prev_word, 1, i);
	return (word_to_find);
}

char	*create_begin_line(t_global *global, char *prev_word, char *line)
{
	t_envp	*node;
	char	*new_string;
	char	*word_to_find;
	char	*begin_line;

	word_to_find = find_word(prev_word);
	node = find_envp_node(word_to_find, global->l_envp);
	begin_line = ft_strdup_be(line, 0, \
	(find_index(line, prev_word) - 1) - ft_strlen(prev_word));
	free(word_to_find);
	if (!node && find_index(line, "$?") == -1)
		new_string = ft_strdup(begin_line);
	else
	{
		if (node)
			word_to_find = ft_strdup_be(node->value, 0, ft_strlen(node->value));
		else
			word_to_find = ft_itoa(g_status);
		new_string = ft_strjoin(begin_line, word_to_find);
		if (ft_strcmp(word_to_find, "0"))
			free(word_to_find);
	}
	free(begin_line);
	return (new_string);
}

char	*new_line(t_global *global, char *to_find, char *copy_line, int mark)
{
	t_envp	*node;
	int		index;
	char	*new_word;
	char	*new_string;
	char	*line;

	index = index_char(copy_line, '$');
	node = find_envp_node(to_find, global->l_envp);
	line = ft_strdup_be(copy_line, 0, index - 1);
	if (node)
	{
		new_word = ft_strdup_be(node->value, 0, ft_strlen(node->value));
		new_string = ft_strjoin(line, new_word);
		free(new_word);
	}
	else
		new_string = ft_strdup(line);
	free(line);
	line = ft_strjoin(new_string, &copy_line[mark]);
	free(new_string);
	return (line);
}

char	*word_to_find(char *copy_line, int index, int *mark, char quote)
{
	char	*word_to_find;

	word_to_find = NULL;
	if (copy_line[index - 1] == 34 || copy_line[index - 1] == 39)
		quote = copy_line[index - 1];
	while (copy_line[*mark] != quote && copy_line[*mark] != ' ' && \
	copy_line[*mark] != '\n')
		(*mark)++;
	word_to_find = ft_strdup_be(copy_line, index + 1, (*mark) - 1);
	return (word_to_find);
}
