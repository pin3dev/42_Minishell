/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_heredoc_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:55:47 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 16:55:49 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_next_line(int fd, int i, char *line)
{
	char	character;
	int		rd;

	rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1);
	line = malloc(100000);
	if (BUFFER_SIZE <= 0)
	{
		free(line);
		return (NULL);
	}
	while (rd > 0)
	{
		line[i] = character;
		i++;
		if (character == '\n')
			break ;
		rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1);
	}
	line[i] = '\0';
	if (rd == -1 || i == 0 || (line[i - 1] && rd == 0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	check_biggest_str(char *token, char *line)
{
	int	s_token;
	int	s_line;
	int	i;

	s_token = 0;
	s_line = 0;
	i = 0;
	while (token[i] && token[i] != '\n')
	{
		s_token++;
		i++;
	}
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		s_line++;
		i++;
	}
	if (s_token > s_line)
		return (s_token);
	else
		return (s_line);
}

void	end_status_heredoc(t_global *global, char *line, char *delimiter)
{
	global->line = line;
	if (delimiter)
		free(delimiter);
}

int	status_here(t_global *global, char *input, char *prev_line, int index)
{
	int		exit;
	int		index_b;
	char	*begin_line;
	char	*line;
	char	*delimiter;

	delimiter = find_delimiter(input);
	line = ft_strdup_be(input, 0, index + 1);
	if (prev_line)
	{
		begin_line = ft_strjoin(line, "/bheredoc/");
		free(line);
		line = concatenate_string(begin_line, prev_line);
		prev_line = ft_strjoin(line, "/eheredoc/");
		free(line);
		index_b = find_index(&input[index], delimiter);
		line = ft_strjoin(prev_line, &input[index_b + index]);
		free(prev_line);
		exit = 0;
	}
	else
		exit = 2;
	end_status_heredoc(global, line, delimiter); 
	return (exit);
}

int	heredoc(char *input, int index, t_global *global, char *delimiter)
{
	char	*line;
	char	*prev_line;

	line = get_next_line(0, 0, NULL);
	prev_line = NULL;
	while (line != NULL)
	{
		if (!ft_strncmp(delimiter, line, check_biggest_str(delimiter, line)))
		{
			free(line);
			break ;
		}
		if (!prev_line)
		{
			prev_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
			ft_strcpy(prev_line, line);
			free(line);
		}
		else
			prev_line = concatenate_string(prev_line, line);
		write(1, "> ", 2);
		line = get_next_line(0, 0, NULL);
	}
	return (status_here(global, input, prev_line, index));
}
