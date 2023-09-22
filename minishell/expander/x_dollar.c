/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_dollar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:27:31 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 21:27:49 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_new_line(t_global *global, char *line, char *new, char **split)
{
	free(line);
	global->line = new;
	free_array(split, true);
}

char	*replace_word(t_global *global, char *prev_w, char *line, char **split)
{
	char	*new_string;
	char	*full_line;
	int		i;
	int		j;
	int		size;

	j = 1;
	new_string = create_begin_line(global, prev_w, line);
	while (ft_isalnum(prev_w[j]))
		j++;
	size = ft_strlen(prev_w) - j - 1;
	i = find_index(line, prev_w) - 1;
	if (find_index(line, "$?") == -1)
		full_line = ft_strjoin(new_string, &line[i - size]);
	else
		full_line = ft_strjoin(new_string, &line[i - size + 1]);
	free(new_string);
	free(line);
	free_array(split, true);
	return (full_line);
}

bool	dollar_sign(t_global *global, char *line, int index, int i)
{
	char	**split;
	char	*new;

	new = ft_strdup(line);
	split = split_tokens(new, 2);
	while (split[++i])
	{
		index = index_char(split[i], '$');
		if (!ft_strcmp(split[i], "<<"))
			new = dollar_heredoc(global, split[i + 1], new, &i);
		else if (index != ft_strlen(split[i]))
		{
			if (*split[i] != 39)
			{
				new = replace_word(global, &split[i][index], new, split);
				split = split_tokens(new, 2);
				i = -1;
			}
		}
	}
	create_new_line(global, line, new, split);
	if (verify_empty_str(global->line, 0))
		return (1);
	else
		return (0);
}
