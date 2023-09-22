/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:06:57 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 14:09:47 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mini_pwd(t_global *global, t_cmd *cmd)
{
	if (cmd->param[0])
		return (print_error("pwd", \
		"Arguments and options aren't supported", NULL), set_new_status(1));
	else
		printf("%s\n", find_envp_node("PWD", global->l_envp)->value);
	set_new_status(0);
}
