/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:38:36 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 18:38:45 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cat_status(int status)
{
	if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	interactive_mode_slash(int sig)
{
	ft_putstr_fd("Quit (core dumped)\n", 1);
	(void)sig;
}

void	interactive_mode_c(int sig)
{
	printf("\n");
	(void)sig;
}

void	prompt_reopen(int sig)
{
	set_new_status(130);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	set_sig(t_sig sig, t_global *global)
{
	if (sig == STATIC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, prompt_reopen);
	}
	else if (sig == INTERACTV)
	{
		signal(SIGQUIT, interactive_mode_slash);
		signal(SIGINT, interactive_mode_c);
	}
	else if (sig == EXT)
		out_exit(g_status, global);
}
