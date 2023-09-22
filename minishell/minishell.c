/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:38:51 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 14:47:52 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	g_status;

void	copy_envp(char **o_envp, t_envp **list)
{
	int	str;

	str = 0;
	while (o_envp[str])
	{
		create_envp_list(o_envp[str], list);
		str++;
	}
}

void	init_minixhell(t_global *global)
{
	global->l_envp = malloc(sizeof(t_envp *) * 1);
	global->l_expo = malloc(sizeof(t_expo *) * 1);
	if (!global->l_envp || !global->l_expo)
		return ;
	*global->l_envp = NULL;
	*global->l_expo = NULL;
	global->paths = NULL;
	global->envp = NULL;
	copy_envp(__environ, global->l_envp);
	copy_paths(global->l_envp, global);
	update_envp_array(global);
	create_export_list(global->l_expo, global->l_envp);
}

void	init_lexer(t_global *global)
{
	global->head_list = malloc(sizeof(t_token *) * 1);
	global->head_ast = malloc(sizeof(t_token *) * 1);
	if (!global->head_list || !global->head_ast)
		return ;
	*global->head_list = NULL;
	*global->head_ast = NULL;
	set_sig(STATIC, NULL);
	global->line = NULL;
	global->tokens = NULL;
	global->fd_out = dup(STDOUT_FILENO);
	global->fd_in = dup(STDIN_FILENO);
	g_status = 0;
}

void	run_minixhell(t_global *global)
{
	char	**tokens;

	if (!verify_empty_str(global->input, 0))
	{
		add_history(global->input);
		if (verify_pipes_redir_quotes(global->input))
		{
			clear_memory(REDO, global);
			if (!verify_heredoc(global->input, global, 0, 0))
			{
				if (!dollar_sign(global, global->line, 0, -1))
				{
					tokens = split_tokens(global->line, 0);
					global->tokens = tokens;
					create_cmd_list(global->tokens, global->head_list, 0, 0);
					create_ast(global->head_list, global->head_ast);
					run_ast(global->head_ast, global);
				}
			}
		}
	}
	dup2(global->fd_in, STDIN_FILENO);
	dup2(global->fd_out, STDOUT_FILENO);
}

int	main(void)
{
	t_global	global;

	init_minixhell(&global);
	init_lexer(&global);
	while (1)
	{
		global.input = readline("cliva% ");
		if (!global.input)
			set_sig(EXT, &global);
		if (global.input)
			run_minixhell(&global);
	}
}
