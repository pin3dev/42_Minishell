/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:27:57 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 17:28:00 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ext_cases(int nbr)
{
	if (nbr == -2147483648)
		return ("-2147483648\0");
	else if (nbr == 0)
		return ("0");
	else
		return (NULL);
}

int	abs_nbr(int nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	else
		return (nbr);
}

int	init_len_nbr(int nbr)
{
	if (nbr < 0)
		return (1);
	else
		return (0);
}

int	nbr_len(int nbr)
{
	int	len;

	len = 1;
	while (nbr > 9)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*itoa;
	int		abs;
	int		len;

	itoa = ext_cases(nbr);
	if (!itoa)
	{
		abs = abs_nbr(nbr);
		len = init_len_nbr(nbr) + nbr_len(abs); 
		itoa = malloc(sizeof(char) * (len + 1));
		if (itoa == NULL)
			return (NULL);
		itoa[len] = '\0';
		len--;
		while (len >= 0)
		{
			itoa[len] = (abs % 10) + 48;
			abs = abs / 10;
			len--;
		}
		if (nbr < 0)
			itoa[0] = '-';
	}
	return (itoa);
}
