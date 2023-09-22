/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lb_lst_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:32:25 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 17:32:26 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_envp(t_envp *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

t_envp	*ft_lstnew_envp(char *name, char *value, char *full)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (new == NULL)
		return (NULL);
	if (new)
	{
		new->name = name;
		new->value = value;
		new->full = full;
		new->next = NULL;
	}
	return (new);
}

void	ft_lstadd_back_envp(t_envp **head, t_envp *new)
{
	t_envp		*begin;

	if (!*head)
	{
		(*head) = new;
		return ;
	}
	if (head && (*head) && new)
	{
		begin = (*head);
		if (begin == NULL)
			(*head) = new;
		else
		{
			while (begin->next)
				begin = begin->next;
			begin->next = new;
		}
	}
}

void	free_envp_lst(t_envp **head)
{
	t_envp	*cur;
	t_envp	*next;

	if (!head)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		free(cur->name);
		free(cur->value);
		free(cur->full);
		free(cur);
		cur = next;
	}
}

void	create_envp_list(char *str, t_envp **list)
{
	int		equalsg;
	char	*name;
	char	*value;
	char	*full;

	equalsg = index_char(str, 61);
	name = ft_strdup_be(str, 0, equalsg - 1);
	value = ft_strdup_be(str, equalsg + 1, ft_strlen(str) - 1);
	full = ft_strdup(str);
	ft_lstadd_back_envp(list, ft_lstnew_envp(name, value, full));
}
/* void print_list_envp(t_envp **head)
{
	t_envp *cur = *head;
	
	while(cur)
	{
		printf("%s\n", cur->full);
		cur = cur->next;
	}
} */