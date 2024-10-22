/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:03:54 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/22 02:21:20 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_setfds(t_execs *exec)
{
	t_list	*list;
	t_fds	*fds;
	int		fdin;
	int		fdout;

	fdin = 0;
	fdout = 1;
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
	if (dup2(fdin, 0) == -1 || dup2(fdout, 1) == -1)
		return (1);
	return (0);
}

static int	ft_closeallfds(t_execs *exec)
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

static int	isbuiltin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (2);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (3);
	if (!ft_strncmp(cmd, "export", 7))
		return (4);
	if (!ft_strncmp(cmd, "unset", 6))
		return (5);
	if (!ft_strncmp(cmd, "env", 4))
		return (6);
	if (!ft_strncmp(cmd, "exit", 5))
		return (7);
	return (0);
}

static int	builtin(t_execs *exec)
{
	int	command;
	int	err;

	command = isbuiltin(((t_execcmd *)exec->cmd)->args[0]);
	if (command == 1)
		err = ft_echo(exec);
	else if (command == 2)
		err = ft_cd(exec);
	else if (command == 3)
		err = ft_pwd(exec);
	else if (command == 4)
		err = ft_export(exec);
	else if (command == 5)
		err = ft_unset(exec);
	else if (command == 6)
		err = ft_env(exec);
	else
		err = ft_exit(exec);
	dup2(exec->stdcopies[0], 0);
	dup2(exec->stdcopies[1], 1);
	return (err);
}

int	ft_sorter(t_execs *exec, t_cmd *cmd)
{
	int	err;

	exec->cmd = cmd;
	err = 0;
	if (g_bigsignal == SIGINT)
		return (exec->ret);
	if (!cmd)
		exec->ret = err;
	else if (cmd->type == EXEC)
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
	else
		err = ft_sub(exec);
	if (cmd && err != 1)
		exec->ret = err;
	return (err);
}

int	ft_exec(t_execs *exec)
{
	t_execcmd	*cmds;
	char		**args;
	int			pid;
	int			err;
	t_shell		*shell;

	if (!exec->cmd || !((t_execcmd *)exec->cmd)->args)
		return (0);
	err = 0;
	cmds = (t_execcmd *)exec->cmd;
	args = cmds->args;
	if (ft_setfds(exec))
		return (333);
	if (!isbuiltin(args[0]))
	{
		signals_exec();
		pid = fork();
		if (!pid)
		{
			ft_closeallfds(exec);
			err = ft_command(exec, cmds);
			if (!err)
			{
				signal(SIGQUIT, SIG_DFL);
				execve(args[0], args, exec->shell->env);
				signal(SIGQUIT, SIG_IGN);
			}
			ft_listfree(&exec->fds, fdsfree);
			shell = exec->shell;
			execfree(exec);
			arrayfree(shell->env);
			free(shell);
			printf("cureent err%d!\n", err);
			exit(err);
		}
		waitpid(pid, &err, 0);
		sleep(5);
		printf("cureent numb %d!\n", err);
		if (g_bigsignal == SIGINT)
		{
			printf("heelo my friend \n");
			// write(2, "\n", 1);
			// rl_on_new_line();
			// rl_replace_line("", 0);
			// rl_redisplay();
		}
		signals();
		if (err == 131)
			write(2, "Quit (core dumped)\n", 20);
	}
	else
		err = builtin(exec);
	if (g_bigsignal == SIGINT)
		err = 130;
	if (err == 1)
		execfree(exec);
	else
		exec->ret = err;
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
		if (!command->args)
			return (0);
		command->args = args(command->args, exec);
		if (!command->args)
			return (execfree(exec), 1);
	}
	return (0);
}

int	executer(t_shell *shell, int err)
{
	t_execs	*exec;

	if (!shell || !shell->tree)
		return (err);
	exec = ft_calloc(sizeof(t_execs), 1);
	exec->shell = shell;
	exec->fds = 0;
	exec->ret = err;
	exec->stdcopies[0] = dup(0);
	exec->stdcopies[1] = dup(1);
	err = ft_expandcmd(exec, shell->tree);
	if (err)
		return (err);
	err = ft_sorter(exec, exec->shell->tree);
	if (err != 1)
		execfree(exec);
	return (err);
}
