/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:03:54 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/13 15:50:31 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iswhite(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

// char	*ft_getenv(char *name, char **ev)
// {
// 	int	i;
// 	int	len;

// 	len = ft_strlen(name);
// 	i = 0;
// 	while(ev[i])
// 	{
// 		if (!ft_strncmp(name, ev[i], len))
// 			return (ft_substr(ev[i], ev[i] + len + 1, ft_strlen(ev[i] + len + 1)))
// 		i++;
// 	}
// 	return (0);
// }

int	seterr(t_execs *exec, int err)
{
	exec->ret = err;
	return (err);
}

int	ft_setfds(t_execs *exec)
{
	t_list	*list;
	t_fds	*fds;
	int		fdin;
	int		fdout;

	fdin = 0;
	fdin = 1;
	list = exec->fds;
	while (list)
	{
		fds = list->data;
		if (fds->type == FD_FILEIN)
			fdin = fds->fd;
		else
			fdout = fds->fd;
		list = list->next;
	}
	dup2(fdin, 0);
	dup2(fdout, 1);
	return (0);
}

int	ft_closeallfds(t_execs *exec)
{
	t_list	*lst;

	lst = exec->fds;
	while (lst)
	{
		close(((t_fds *)lst->data)->fd);
		lst = lst->next;
	}
	return (0);
}

int	isbuiltin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (0);
	if (!ft_strncmp(cmd, "cd", 3))
		return (0);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (0);
	if (!ft_strncmp(cmd, "export", 7))
		return (0);
	if (!ft_strncmp(cmd, "unset", 6))
		return (0);
	if (!ft_strncmp(cmd, "env", 4))
		return (0);
	if (!ft_strncmp(cmd, "exit", 5))
		return (0);
	return (1);
}

int	ft_sorter(t_execs *exec, t_cmd *cmd)
{
	int	err;

	exec->cmd = cmd;
	if (!cmd)
		err = ft_exec(exec);
	if (cmd->type == EXEC)
		err = ft_exec(exec);
	else if (cmd->type == PIPE)
		err = ft_pipe(exec);
	else if (cmd->type == REDIR)
		err = ft_redir(exec);
	else if (cmd->type == AND)
		err = ft_and(exec);
	else if (cmd->type == OR)
		err = ft_or(exec);
	else if (cmd->type == HERE)
		err = ft_here(exec);
	else if (cmd->type == SUB)
		err = ft_sub(exec);
	return (err);
}

int	ft_exec(t_execs *exec)
{
	t_execcmd	*cmds;
	char		**args;
	int			pid;
	int			err;

	if (!exec->cmd)
		return (seterr(exec, 0));
	cmds = (t_execcmd *)exec->cmd;
	args = cmds->args;
	if (!ft_setfds(exec))
		return (1);
	if (isbuiltin(args[0]))
	{
		pid = fork();
		if (!pid)
		{
			ft_closeallfds(exec);
			execve(args[0], args, exec->shell->env);
			// error management
		}
		waitpid(pid, &err);
	}
	else
		err = builtin(args, exec);
	return (err);
}

int	ft_expandcmd(t_execs *exec, t_cmd *cmd)
{
	t_execcmd	*command;

	if (!cmd)
		return (0);
	if (cmd->type == REDIR || cmd->type == HERE)
		return (ft_expandcmd(exec, ((t_redircmd *)cmd)->cmd));
	else if (cmd->type == EXEC)
	{
		command = (t_execcmd *)cmd;
		command->args = args(command->args, exec);
		if (!command->args)
			return (exec->ret);
	}
	return (0);
}

int	executer(t_shell *shell)
{
	int	err;
	t_execs	*exec;

	if (!shell || !shell->tree)
		return ;
	exec = ft_calloc(sizeof(t_execs), 1);
	exec->shell = shell;
	exec->fds = 0;
	exec->ret = 0;
	err = ft_expandcmd(exec, shell->tree);
	if (err)
	{
		// free exec
		return (err);
	}
	err = ft_sorter(exec, exec->shell);
	return (err);
}
