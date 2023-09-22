/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:10:32 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 14:07:37 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_var(char *new_var, t_global *global)
{
	t_envp	*exist;
	char	*name;
	char	*value;
	int		equalsg;

	equalsg = index_char(new_var, 61);
	name = ft_strdup_be(new_var, 0, equalsg - 1);
	value = ft_strdup_be(new_var, equalsg + 1, ft_strlen(new_var) - 1);
	exist = find_envp_node(name, global->l_envp);
	if (!alpha_arg(name))
		return (print_error("export", \
			"not a valid identifier", NULL), set_new_status(1));
	insert_sorted(global->l_expo, name);
	if (exist)
		modify_envp_node(value, exist);
	else
		create_envp_list(new_var, global->l_envp);
	if (!ft_strcmp(name, "PATH"))
		copy_paths(global->l_envp, global);
	free(name);
	free(value);
	update_envp_array(global);
	exist = NULL;
}

char	*concatenate_export_name(char **params, int *i)
{
	char	*name;
	char	*new_name;

	new_name = ft_strdup(params[*i]);
	(*i)++;
	while (params[*i] && !verify_empty_str(params[*i], 0))
	{
		name = ft_strjoin(new_name, params[*i]);
		free(new_name);
		new_name = ft_strdup(name);
		free(name);
		(*i)++;
	}
	(*i)--;
	return (new_name);
}

char	*new_command_param(t_global *global, char *command)
{
	int		i;
	char	*line;
	char	*new_param;

	i = 0;
	line = ft_strdup_be(global->line, find_index(global->line, \
		command), ft_strlen(global->line));
	while (line[i])
	{
		if (token_type(line[i]) == PIPES || token_type(line[i]) == REDIRECTION)
		{
			if (echo_quotes_aux(line, i))
				break ;
		}
		i++;
	}
	new_param = ft_strdup_be(line, 0, i - 1);
	free(line);
	return (new_param);
}

void	exec_export(char **params, t_global *global, int i)
{
	char	*new;

	while (params[++i])
	{
		if (verify_empty_str(params[i], 0))
			i++;
		new = concatenate_export_name(params, &i);
		if (index_char(new, 61) == ft_strlen(new))
		{
			if (!alpha_arg(new))
			{
				print_error("export", new, "not a valid identifier");
				set_new_status(1);
				free(new);
				free_array(params, true);
				return ;
			}
			insert_sorted(global->l_expo, new);
		}
		else
			export_var(new, global);
		free(new);
	}
	free_array(params, true);
}

void	mini_export(char **new_var, t_global *global)
{
	char	*new;
	char	**params;

	if (!*new_var)
		print_expo_list(global->l_expo, global->l_envp);
	else
	{
		new = new_command_param(global, "export");
		params = split_tokens(new, 1);
		free(new);
		exec_export(params, global, -1);
	}
	set_new_status(0);
}
