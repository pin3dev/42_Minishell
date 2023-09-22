/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lst_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:51:15 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/19 16:53:56 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_type(char *redir)
{
	if (!ft_strcmp(redir, ">>"))
		return (APPEND);
	if (!ft_strcmp(redir, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(redir, ">"))
		return (OUT_R);
	if (!ft_strcmp(redir, "<"))
		return (IN_R);
	else
		return (NDA);
}

void	end_pipe(char **str, int *s, t_token **head)
{
	if (str[*s])
	{
		if (!ft_strcmp(str[*s], "|"))
			ft_lstadd_back_list_ast(head, fill_pipe_node(&str[*s]));
		(*s)++;
		create_cmd_list(&str[*s], head, 0, 0);
	}
}

t_token	*begin_cmd_or_redir(char **str, int *s, int *i, t_token **head)
{
	t_token	*cmd;

	cmd = NULL;
	if (redir_type(str[*s]))
	{
		ft_lstadd_back_list_ast(head, fill_redir_node(&str[*s]));
		(*s)++;
	}
	else if (str[*s] && !redir_type(str[*s]) && ft_strcmp(str[*s], "|"))
	{
		cmd = fill_cmd_node(str[*s], *i, 0, NULL);
		ft_lstadd_back_list_ast(head, cmd);
		(*i)++;
	}
	return (cmd);
}

void	create_cmd_list(char **str, t_token **head, int s, int i)
{
	t_token	*cmd;

	cmd = begin_cmd_or_redir(str, &s, &i, head);
	while (str[++s] && ft_strcmp(str[s], "|"))
	{
		if (redir_type(str[s]))
		{
			ft_lstadd_back_list_ast(head, fill_redir_node(&str[s]));
			s++;
		}
		else
		{
			if (cmd)
				fill_cmd_node(str[s], i, 1, cmd);
			else
			{
				cmd = fill_cmd_node(str[s], i, 0, cmd);
				ft_lstadd_back_list_ast(head, cmd);
			}
			i++;
		}
	}
	if (cmd)
		fill_cmd_node(NULL, i, 2, cmd);
	end_pipe(str, &s, head);
}
