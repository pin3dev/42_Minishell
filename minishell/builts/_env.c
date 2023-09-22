/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:07:38 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 13:50:29 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mini_env(t_envp **head, t_cmd *cmd)
{
	t_envp	*cur;

	if (cmd->param[0])
		return (print_error("env", \
		"Arguments and options aren't supported", NULL), set_new_status(1));
	else
	{
		cur = *head;
		while (cur)
		{
			printf("%s\n", cur->full);
			cur = cur->next;
		}
	}
	set_new_status(0);
}
