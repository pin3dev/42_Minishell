/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:37:25 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 18:37:38 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_new_status(int exit_status)
{
	g_status = exit_status;
}

int	index_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	print_str(char *s, int fd)
{
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(s, fd);
}

void	print_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd("minixHell", 2);
	if (s1)
		print_str(s1, 2);
	if (s2)
		print_str(s2, 2);
	if (s3)
		print_str(s3, 2);
	ft_putstr_fd("\n", 2);
}
