/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:11:02 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 17:11:03 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
		ft_putchar_fd(s[i++], fd);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (0);
	else
		return (1);
}

int	ft_strncmp(char *str1, char *str2, int n)
{
	int	i;
	int	len;

	i = 0;
	len = n;
	if (n == 0)
		return (0);
	while (str1[i] != '\0' && str2[i] != '\0' && len - 1 > 0)
	{
		if (str1[i] == str2[i])
		{
			i++;
			len--;
		}
		else
			break ;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
