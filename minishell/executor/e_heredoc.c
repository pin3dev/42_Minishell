/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:44:04 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 18:44:21 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredocnizer(t_token *cur, t_global *global)
{
	int		fds[2];
	pid_t	pid;

	pipe(fds);
	pid = forknize();
	if (pid == 0)
	{
		close(fds[READ]);
		if (duplicate(fds[WRITE], STDOUT_FILENO) < 0)
			return ;
		write(STDOUT_FILENO, cur->redir->file, ft_strlen(cur->redir->file));
		close(fds[WRITE]);
		exit(EXIT_SUCCESS);
	}
	else 
	{
		close(fds[WRITE]);
		if (duplicate(fds[READ], STDIN_FILENO) < 0)
			return ;
		run_ast(&cur->redir->next_tok, global);
		close(fds[READ]);
		waitpid(pid, &g_status, 0);
		set_new_status(cat_status(g_status));
	}
}
