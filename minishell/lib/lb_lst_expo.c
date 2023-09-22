/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lb_lst_expo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:35:20 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 17:35:53 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_expo_list(t_expo **l_expo, t_envp **l_envp)
{
	t_expo	*cur_exp;
	t_envp	*cur_env;

	cur_exp = *l_expo;
	cur_env = *l_envp;
	while (cur_exp)
	{
		cur_env = find_envp_node(cur_exp->name, l_envp);
		if (!cur_env)
			printf("%s%s\n", cur_exp->prefix, cur_exp->name);
		else
			printf("%s%s%s\"%s\"\n", cur_exp->prefix, \
			cur_env->name, "=", cur_env->value);
		cur_exp = cur_exp->next;
	}
}

t_expo	*ft_lstnew_export(char *name)
{
	t_expo	*new;

	new = malloc(sizeof(t_expo));
	if (new == NULL)
		return (NULL);
	if (new)
	{
		new->prefix = "declare -x ";
		new->name = name;
		new->next = NULL;
	}
	return (new);
}

void	insert_sorted(t_expo **head, char *name)
{
	t_expo	*new;
	t_expo	*cur;
	char	*var_name;

	new = find_expo_node(name, head);
	if (new)
		return ;
	var_name = ft_strdup(name);
	new = ft_lstnew_export(var_name);
	cur = *head;
	if (!cur || cmp_sort_str(var_name, cur->name) < 0) 
	{
		new->next = cur;
		*head = new;
	}
	else
	{
		while (cur->next && cmp_sort_str(var_name, cur->next->name) > 0)
			cur = cur->next;
		new->next = cur->next;
		cur->next = new;
	}
}

void	create_export_list(t_expo **l_expo, t_envp **l_envp)
{
	t_envp	*cur;

	cur = *l_envp;
	if (cur)
	{
		while (cur)
		{
			insert_sorted(l_expo, cur->name);
			cur = cur->next;
		}
	}
}

void	free_expo_lst(t_expo **head)
{
	t_expo	*cur;
	t_expo	*next;

	if (!head)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		free(cur->name);
		free(cur);
		cur = next;
	}
}
