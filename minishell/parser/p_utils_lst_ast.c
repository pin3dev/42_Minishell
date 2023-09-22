/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:53:04 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 18:53:14 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*fill_pipe_node(char **str)
{
	t_token	*node;

	(void)str;
	node = ft_lstnew_list_ast(PIPE);
	node->pipe = malloc(sizeof(t_redir) * 1);
	if (!node || !node->pipe)
		return (NULL);
	node->pipe->left = NULL;
	node->pipe->right = NULL;
	return (node);
}

void	fill_type_redir_node(t_redir *redir, int fd, int mode)
{
	redir->fd = fd;
	redir->mode = mode;
	redir->next_tok = NULL;
}

t_token	*fill_redir_node(char **str)
{
	t_token	*node;

	node = ft_lstnew_list_ast(REDIR);
	node->redir = malloc(sizeof(t_redir) * 1);
	if (!node || !node->redir)
		return (NULL);
	if (redir_type(*str) == HEREDOC)
		fill_type_redir_node(node->redir, 0, -1);
	if (redir_type(*str) == IN_R)
		fill_type_redir_node(node->redir, STDIN_FILENO, O_RDONLY);
	else if (redir_type(*str) == APPEND)
		fill_type_redir_node(node->redir, STDOUT_FILENO, \
							O_WRONLY | O_CREAT | O_APPEND);
	else if (redir_type(*str) == OUT_R)
		fill_type_redir_node(node->redir, STDOUT_FILENO, \
							O_WRONLY | O_CREAT | O_TRUNC);
	++str;
	node->redir->file = *str;
	return (node);
}

void	finish_cmd_node(t_token *node, int index)
{
	int	i;

	i = 1;
	node->cmd->full_cmd[index] = NULL;
	node->cmd->name = node->cmd->full_cmd[0];
	while (node->cmd->full_cmd[i])
	{
		node->cmd->param[i - 1] = node->cmd->full_cmd[i];
		i++;
	}
	node->cmd->param[i - 1] = NULL;
}

t_token	*fill_cmd_node(char *str, int index, int finish, t_token *node)
{
	if (!node)
	{
		node = ft_lstnew_list_ast(CMD);
		node->cmd = malloc(sizeof(t_cmd) * 1);
		if (!node || !node->cmd)
			return (NULL);
	}
	if (str)
		node->cmd->full_cmd[index] = ft_strdup_be(str, 0, ft_strlen(str));
	if (finish == 1)
		return (NULL);
	if (finish == 2)
	{
		finish_cmd_node(node, index);
		return (NULL);
	}
	return (node);
}
