/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils_expo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:12:51 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 13:13:22 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expo	*find_prev_expo_node(char *name, t_expo **list)
{
	t_expo	*cur;

	cur = *list;
	while (ft_strcmp(cur->next->name, name) != 0)
		cur = cur->next;
	return (cur);
}

t_expo	*find_expo_node(char *name, t_expo **list)
{
	t_expo	*cur;

	cur = *list;
	while (cur && ft_strcmp(cur->name, name) != 0)
		cur = cur->next;
	return (cur);
}

int	cmp_sort_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
