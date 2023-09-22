/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:18:24 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 18:18:35 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **array, bool flag)
{
	int	s;

	s = 0;
	while (array[s])
	{
		free(array[s]);
		s++;
	}
	*array = NULL;
	if (flag == true)
		free(array);
}

void	clear_enviroment(t_global *global)
{
	if (*global->l_envp)
		free_envp_lst(global->l_envp);
	if (*global->l_expo)
		free_expo_lst(global->l_expo);
	if (*global->envp)
		free_array(global->envp, false);
	if (*global->paths)
		free_array(global->paths, false);
}

void	clear_exit(t_global *global)
{
	if (global->envp || global->l_envp || global->paths || global->l_expo)
		clear_enviroment(global);
	if (global->tokens)
		free_array(global->tokens, false);
	if (global->head_list)
		clear_ast(global->head_list);
	free(global->tokens);
	free(global->head_ast);
	free(global->head_list);
	free(global->l_envp);
	free(global->l_expo);
	free(global->envp);
	free(global->paths);
	if (global->line)
		free(global->line);
}

void	clear_redo(t_global *global)
{
	if (global->tokens)
		free_array(global->tokens, true);
	global->tokens = NULL;
	if (global->head_list)
		clear_ast(global->head_list);
	*(global->head_list) = NULL;
	*(global->head_ast) = NULL;
	if (global->line)
		free(global->line);
}

void	clear_memory(int flag, t_global *global)
{
	if (flag == EXT)
		clear_exit(global);
	if (flag == REDO)
		clear_redo(global);
}
