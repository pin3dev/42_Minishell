/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:31:45 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 18:32:51 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	duplicate(int fd_dest, int fd_src)
{
	int	st;

	st = dup2(fd_dest, fd_src);
	if (st != -1)
		return (st);
	print_error("dup2", strerror(errno), NULL);
	set_new_status(1);
	return (-1);
}

static pid_t	exec_left(int fds[2], t_token *cur, t_global *global)
{
	pid_t	pid;

	pid = forknize();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (duplicate(fds[WRITE], STDOUT_FILENO) < 0)
			return (-1);
		close(fds[WRITE]);
		close(fds[READ]);
		run_ast(&cur, global);
		exit(g_status);
	}
	return (pid);
}

static pid_t	exec_right(int fds[2], t_token *cur, t_global *global)
{
	pid_t	pid;

	pid = forknize();
	if (pid == 0)
	{
		if (duplicate(fds[READ], STDIN_FILENO) < 0)
			return (-1);
		close(fds[READ]);
		close(fds[WRITE]);
		run_ast(&cur, global);
		exit(g_status);
	}
	return (pid);
}

int	set_pipe(int fds[2])
{
	int	check;

	check = pipe(fds);
	if (!check)
		return (0);
	print_error("pipe", strerror(errno), NULL);
	set_new_status(1);
	return (-1);
}

void	pipenizer(t_token *cur, t_global *global)
{
	int		fds[2];
	pid_t	pid_read;
	pid_t	pid_write;

	if (set_pipe(fds) < 0)
		return ;
	pid_write = exec_left(fds, cur->pipe->left, global);
	if (pid_write < 0)
		return ;
	pid_read = exec_right(fds, cur->pipe->right, global);
	if (pid_read < 0)
		return ;
	close(fds[READ]);
	close(fds[WRITE]);
	waitpid(pid_write, &g_status, 0);
	waitpid(pid_read, &g_status, 0);
	set_new_status(cat_status(g_status));
}
