/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_upd_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:52:40 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 12:57:39 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_paths(t_envp **list, t_global *global)
{
	t_envp	*node;

	node = find_envp_node("PATH", list);
	if (global->paths)
		free_array(global->paths, false);
	if (node)
		global->paths = ft_split(node->value, ':');
}

void	update_envp_array(t_global *global)
{
	t_envp	*cur;
	int		s;

	s = 0;
	if (global->envp)
		free_array(global->envp, true);
	cur = *(global->l_envp);
	global->envp = ft_calloc(ft_lstsize_envp(cur) + 1, sizeof(char *));
	while (cur)
	{
		global->envp[s] = ft_calloc(ft_strlen(cur->full) + 1, sizeof(char));
		ft_strcpy(global->envp[s], cur->full);
		s++;
		cur = cur->next;
	}
	global->envp[s] = NULL;
}
