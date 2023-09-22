/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:10:20 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 13:12:18 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	modify_envp_node(char *value, t_envp *node)
{
	char	*name_eq;

	if (node)
	{
		free(node->value);
		free(node->full);
		node->value = ft_strdup(value);
		name_eq = ft_strjoin(node->name, "=");
		node->full = ft_strjoin(name_eq, node->value);
		free(name_eq);
	}
}

t_envp	*find_envp_node(char *name, t_envp **list)
{
	t_envp	*cur;

	cur = *list;
	while (cur && ft_strcmp(cur->name, name) != 0)
		cur = cur->next;
	return (cur);
}

t_envp	*find_prev_envp_node(char *name, t_envp **list)
{
	t_envp	*cur;

	cur = *list;
	while (ft_strcmp(cur->next->name, name) != 0)
		cur = cur->next;
	return (cur);
}
