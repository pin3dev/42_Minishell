/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:47:19 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 18:47:31 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	priority_reorder(t_token *tmp, t_token *cur, t_token **side)
{
	*side = tmp;
	tmp->redir->next_tok = cur;
}

void	priority_pass(t_token *cur, t_token *end, t_token **side)
{
	t_token	*last;
	t_token	*tmp;
	t_div	type;

	tmp = NULL;
	last = cur;
	type = cur->type;
	while (cur != end)
	{
		tmp = cur->next;
		if (tmp == NULL)
			break ;
		if (tmp->type < type)
		{
			last->redir->next_tok = tmp;
			if (tmp->next != end)
				priority_reorder(tmp->next, cur, side);
			cur = cur->next;
		}
		else if (tmp != end)
			priority_reorder(tmp, cur, side);
		else
			*side = cur;
		cur = cur->next;
	}
}

void	organize_ast(t_token *begin, t_token *end, t_token **side)
{
	t_token	*cur;

	if (begin->type != PIPE)
	{
		cur = begin;
		*side = begin;
	}
	else
	{
		cur = begin->next;
		*side = begin->next;
	}
	priority_pass(cur, end, side);
}

void	create_ast(t_token **head_list, t_token **head_ast)
{
	t_token	*cur;

	cur = *head_list;
	while (cur)
	{
		if (cur->type == PIPE)
		{
			*head_ast = cur;
			organize_ast(*head_list, cur, &cur->pipe->left);
			find_pipes(*head_ast);
			break ;
		}
		cur = cur->next;
	}
	if (!cur)
		organize_ast(*head_list, cur, head_ast);
}
