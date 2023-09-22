/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lb_lst_ast_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:26:12 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 18:26:23 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipe(t_token *cur)
{
	cur->pipe->left = NULL;
	cur->pipe->right = NULL;
	free(cur->pipe);
}

void	free_redir(t_token *cur)
{
	cur->redir->file = NULL;
	cur->redir->fd = 0;
	cur->redir->mode = 0;
	cur->redir->next_tok = NULL;
	free(cur->redir);
}

void	free_cmd(t_token *cur)
{
	cur->cmd->name = NULL;
	free_array(cur->cmd->full_cmd, false);
	free(cur->cmd);
}

void	clear_ast(t_token **head)
{
	t_token	*cur;
	t_token	*next;

	if (!head)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		if (cur->type == PIPE)
			free_pipe(cur);
		else if (cur->type == REDIR)
			free_redir(cur);
		else if (cur->type == CMD)
			free_cmd(cur);
		free(cur);
		cur = next;
	}
}
