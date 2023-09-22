/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:17:01 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 17:17:03 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy2(char *dest, char *src, int size)
{
	unsigned int	i;

	i = 0; 
	while (src[i] != '\0' && size > 0) 
	{
		dest[i] = src[i]; 
		i++;
		size--;
	}
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	unsigned int	i;

	i = 0; 
	while (src[i] != '\0') 
	{
		dest[i] = src[i]; 
		i++;
	}
	dest[i] = '\0'; 
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len;
	int		i;

	len = 0;
	while (s[len])
		len++;
	dest = malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup_be(const char *s, int begin, int end)
{
	char	*dest;
	int		len;
	int		i;

	len = end - begin + 1;
	dest = malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (begin <= end)
	{
		dest[i] = s[begin];
		i++;
		begin++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*string;
	int		len;
	int		i;
	int		b;

	i = 0;
	b = 0;
	if (!s1)
		return (NULL);
	if (!s2 && s1)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	string = malloc(len + 1 * sizeof(char));
	if (string == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		string[i] = s1[i];
		i++;
	}
	while (s2[b] != '\0')
		string[i++] = s2[b++];
	string[i] = '\0';
	return (string);
}
