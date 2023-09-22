/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lb_lst_ast_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:37:01 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 17:37:11 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstnew_list_ast(t_div type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	if (new)
	{
		new->type = type;
		new->cmd = NULL;
		new->pipe = NULL;
		new->redir = NULL;
		new->next = NULL;
	}
	return (new);
}

/* t_token	*ft_lstlast_ast(t_token *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	else
		return (NULL);
	return (lst);
} */

void	ft_lstadd_back_list_ast(t_token **head, t_token *new)
{
	t_token		*begin;

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
