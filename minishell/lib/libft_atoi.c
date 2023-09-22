/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:29:19 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 17:29:21 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

const char	*ft_skip_spaces(const char *str)
{
	while (*str == '\t' || *str == '\n' || *str == '\v' || \
*str == '\f' || *str == '\r' || *str == ' ')
		++str;
	if (*str == '\0')
		exit (2);
	return (&(*str));
}

int	ft_atoi(const char *str)
{
	long long int	ret;
	int				sign;

	ret = 0;
	sign = 1;
	str = ft_skip_spaces(str);
	if (*str && (*str == 43 || *str == 45))
	{
		if (*str == 45)
			sign = -1;
		if (!ft_isdigit(*++str))
			exit (2);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			exit (2);
		ret *= 10;
		ret += (sign * (*(str++) - 48));
	}
	if (ret > 2147483647 || ret < -2147483648)
		exit(1);
	return (ret);
}
