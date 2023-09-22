/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:15:38 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 14:12:48 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_expo_node(char *name_var, t_expo **l_expo)
{
	t_expo	*node_prev;
	t_expo	*node_to_free;

	node_to_free = find_expo_node(name_var, l_expo);
	if (node_to_free == *(l_expo))
		*(l_expo) = node_to_free->next;
	else
	{
		node_prev = find_prev_expo_node(name_var, l_expo);
		if (node_to_free->next)
			node_prev->next = node_to_free->next;
		else
			node_prev->next = NULL;
	}
	free(node_to_free->name);
	node_to_free->next = NULL;
	free(node_to_free);
}

void	remove_envp_node(char *name_var, t_envp *to_free, t_global *global)
{
	t_envp	*node_prev;

	node_prev = NULL;
	if (to_free == *(global->l_envp))
		*(global->l_envp) = to_free->next;
	else
	{
		node_prev = find_prev_envp_node(name_var, global->l_envp);
		if (to_free->next)
			node_prev->next = to_free->next;
		else
			node_prev->next = NULL;
	}
	free(to_free->name);
	free(to_free->value);
	free(to_free->full);
	to_free->next = NULL;
	free(to_free);
}

void	mini_unset(char **name_var, t_global *global)
{
	t_envp	*node_to_free;
	int		i;

	i = 0;
	if (!name_var[i])
		return (set_new_status(0));
	while (name_var[i])
	{
		if (!alpha_arg(name_var[i]))
			return (print_error("unset", name_var[i], \
				"Arguments and options aren't supported"), set_new_status(1));
		if (!ft_strcmp(name_var[i], "PATH"))
			free_array(global->paths, false);
		node_to_free = find_envp_node(name_var[i], global->l_envp);
		if (node_to_free)
		{
			remove_envp_node(name_var[i], node_to_free, global);
			remove_expo_node(name_var[i], global->l_expo);
		}
		else
			remove_expo_node(name_var[i], global->l_expo);
		update_envp_array(global);
		i++;
	}
	set_new_status(0);
}
