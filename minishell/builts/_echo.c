/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:44:16 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 13:48:55 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_new_line(int *i, int *new_line, int *flag_n)
{
	(*i)++;
	*flag_n = 1;
	*new_line = 0;
}

void	skip_n(char *str, int *c)
{
	(*c)++;
	while (str[*c] == 'n')
		(*c)++;
}

void	print_character(char *str, int *i, int *new_line, int *flag_n)
{
	int	c;
	int	index;

	c = -1;
	while (str[++c])
	{
		if (str[c] == '-' && str[c + 1] == 'n' && c == 0)
		{
			index = c;
			if (*i == 1 || *flag_n == 1)
			{
				skip_n(str, &c);
				if (str[c] == '\0')
				{
					no_new_line(i, new_line, flag_n);
					break ;
				}
				else
					c = index;
			}
		}
		*flag_n = 0;
		if (str[c] != '\0')
			write(1, &str[c], 1);
	}
}

void	start_echo(char **split, int i)
{
	int	flag_n;
	int	new_line;

	flag_n = 0;
	new_line = 1;
	i = 1;
	while (split[i])
	{
		print_character(split[i], &i, &new_line, &flag_n);
		if (split[i] != NULL)
			i++;
	}
	if (new_line == 1)
		write(1, "\n", 1);
}

void	mini_echo(t_global *global, char *new_param)
{
	char	**split;

	new_param = new_command_param(global, "echo");
	split = split_tokens(new_param, 1);
	free(new_param);
	start_echo(split, 1);
	free_array(split, true);
	set_new_status(0);
}
