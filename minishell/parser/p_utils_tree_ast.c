/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:50:03 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 18:50:12 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*find_div_node(t_div type, t_token *begin, t_token *end)
{
	t_token	*cur;

	cur = begin->next;
	while (cur != end)
	{
		if (cur->type == type)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void	find_pipes(t_token *begin)
{
	t_token	*cur;
	t_token	*pipe;

	cur = NULL;
	pipe = begin;
	while (1)
	{
		cur = find_div_node(PIPE, pipe, NULL);
		if (!cur)
		{
			organize_ast(pipe, cur, &pipe->pipe->right);
			break ;
		}
		pipe->pipe->right = cur;
		organize_ast(pipe, cur, &cur->pipe->left);
		pipe = cur;
	}
}
