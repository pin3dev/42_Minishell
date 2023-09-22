/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:03:47 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 14:00:37 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	out_exit(int n, t_global *global)
{
	write(1, "exit\n", 5);
	clear_memory(EXT, global);
	exit(n);
}

void	mini_exit(char **param, t_global *global)
{
	int	n;

	if (param[0])
	{
		if (!digit_arg(param[0]))
			return (print_error("exit", param[0], \
				"numeric argument required"), out_exit(2, global));
		if (count_param(param) > 1)
			return (print_error("exit", \
				"too many arguments", NULL), set_new_status(1));
		n = ft_atoi(param[0]);
		if (n)
			out_exit(n, global);
	}
	else
		out_exit(g_status, global);
}
