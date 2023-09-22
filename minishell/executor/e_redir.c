/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:30:35 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 18:30:48 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_redirs(t_token *first)
{
	t_token	*cur;

	if (first->redir->next_tok)
	{
		cur = first->redir->next_tok;
		while (cur->redir)
		{
			if (cur->redir->fd == first->redir->fd)
				cur->redir->fd = -1;
			cur = cur->redir->next_tok;
		}
	}
}

void	redinizer(t_token *cur, t_global *global)
{
	int	fd_cur;

	if (access(cur->redir->file, F_OK) == -1 && cur->redir->fd == 0)
	{
		print_error("open", cur->redir->file, strerror(errno));
		set_new_status(1);
	}
	else
	{
		if (cur->redir->fd != -1)
		{
			close(cur->redir->fd);
			open(cur->redir->file, cur->redir->mode, 00644);
			check_redirs(cur);
		}
		else
		{
			fd_cur = open(cur->redir->file, cur->redir->mode, 00644);
			close(fd_cur);
		}
		if (cur->redir->next_tok)
			run_ast(&cur->redir->next_tok, global);
	}
}
