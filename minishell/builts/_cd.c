/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:05:09 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 13:42:16 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_to_home(t_global *global)
{
	t_envp	*home;

	home = find_envp_node("HOME", global->l_envp);
	if (!home)
		return (print_error("cd", \
			"HOME not set", NULL), set_new_status(1));
	else if (chdir((const char *)home->value) != 0)
		return (print_error("cd", \
			strerror(errno), NULL), set_new_status(1));
}

void	mini_cd(char **path, t_global *global)
{
	char	oldpwd[1024];
	char	pwd[1024];

	if (count_param(path) > 1)
		return (print_error("cd", "too many arguments", \
				NULL), set_new_status(1));
	else
	{
		getcwd(oldpwd, sizeof(oldpwd));
		modify_envp_node(oldpwd, find_envp_node("OLDPWD", global->l_envp));
		if (!path[0])
			go_to_home(global);
		else if (chdir((const char *)path[0]) != 0)
			return (print_error("cd", path[0], \
				strerror(errno)), set_new_status(1));
		getcwd(pwd, sizeof(pwd));
		modify_envp_node(pwd, find_envp_node("PWD", global->l_envp));
		update_envp_array(global);
		set_new_status(0);
	}
}
