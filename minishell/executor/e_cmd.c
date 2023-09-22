/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:29:13 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/18 18:29:22 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	forknize(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("fork", strerror(errno), NULL);
		set_new_status(127);
	}
	return (pid);
}

char	*cat_exec(t_cmd *cmd, t_global *global)
{
	int		i;
	char	*cmd_slash;
	char	*cmd_path;

	if (cmd->name[0] == '/' || (cmd->name[0] == '.' && cmd->name[1] == '/'))
		return (cmd->name);
	i = 0;
	while (global->paths[i])
	{
		cmd_slash = ft_strjoin(global->paths[i], "/");
		cmd_path = ft_strjoin(cmd_slash, cmd->name);
		free(cmd_slash);
		if (access(cmd_path, X_OK) == -1)
		{
			free(cmd_path);
			i++;
		}
		else
			return (cmd_path);
	}
	print_error(cmd->name, "command not found", NULL);
	set_new_status(127);
	return (NULL);
}

void	execve_command(t_cmd *cmd, t_global *global, char *path)
{
	pid_t	pid;

	path = cat_exec(cmd, global);
	if (path)
	{
		set_sig(INTERACTV, NULL);
		pid = forknize();
		if (pid == 0)
		{
			execve(path, cmd->full_cmd, global->envp);
			print_error("execve", strerror(errno), NULL);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		else
		{
			waitpid(pid, &g_status, 0);
			if (cmd->name[0] != '/' && cmd->name[0] != '.' \
			&& cmd->name[1] != '/')
				free(path);
			set_sig(STATIC, NULL);
			set_new_status(cat_status(g_status));
		}
	}
}

void	exec_builts(t_cmd *cmd, t_global *global)
{
	if (!ft_strcmp(cmd->name, "echo"))
	{
		if (!cmd->param[0])
			printf("\n");
		else 
			mini_echo(global, NULL);
	}
	else if (!ft_strcmp(cmd->name, "cd"))
		mini_cd(cmd->param, global);
	else if (!ft_strcmp(cmd->name, "pwd"))
		mini_pwd(global, cmd);
	else if (!ft_strcmp(cmd->name, "export"))
		mini_export(cmd->param, global);
	else if (!ft_strcmp(cmd->name, "unset"))
		mini_unset(cmd->param, global);
	else if (!ft_strcmp(cmd->name, "env"))
		mini_env(global->l_envp, cmd);
	else if (!ft_strcmp(cmd->name, "exit"))
		mini_exit(cmd->param, global);
	else
		execve_command(cmd, global, NULL);
}

void	run_ast(t_token **token, t_global *global)
{
	t_token	*cur;

	cur = *token;
	if (cur->type == PIPE)
		pipenizer(cur, global);
	else if (cur->type == REDIR)
	{
		if (cur->redir->mode == -1)
		{
			if (cur->redir->next_tok)
				heredocnizer(cur, global);
			else
				return ;
		}
		else
			redinizer(cur, global);
	}
	else if (cur-> type == CMD)
		exec_builts(cur->cmd, global);
}
