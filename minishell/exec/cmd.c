/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:03:54 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/28 13:20:35 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		err = ft_exec(exec, 0, (t_execcmd *)cmd);
	else if (cmd->type == PIPE)
		err = ft_pipe(exec, 0, (t_pipecmd *)cmd);
	else if (cmd->type == REDIR)
		err = ft_redir(exec, 0, (t_redircmd *)cmd);
	else if (cmd->type == AND)
		err = ft_and(exec, 0, (t_andcmd *)cmd);
	else if (cmd->type == OR)
		err = ft_or(exec, 0, (t_orcmd *)cmd);
	else if (cmd->type == HERE)
		err = ft_here(exec, 0, (t_redircmd *)cmd);
	else
		err = ft_sub(exec, 0, (t_sub *)cmd);
	if (cmd && err != 1)
		exec->ret = err;
	return (err);
}

static int	ft_exec3(int err)
{
	if (WIFSIGNALED(err) && WTERMSIG(err) == SIGINT)
		g_bigsignal = SIGINT;
	if (WIFEXITED(err))
		err = WEXITSTATUS(err);
	if (err == 1)
		err = 333;
	if (err == 131 && g_bigsignal != SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	return (err);
}

static int	ft_exec2(t_execs *exec, char **args, int err, t_execcmd *cmds)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		if (ft_setfds(exec))
			exit_execfree(exec, 333);
		ft_closeallfds(exec);
		err = ft_command(exec, cmds, 0, 0);
		if (!err)
		{
			signal(SIGQUIT, SIG_DFL);
			execve(args[0], args, exec->shell->env);
			signal(SIGQUIT, SIG_IGN);
		}
		exit_execfree(exec, err);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &err, 0);
	return (ft_exec3(err));
}

int	ft_exec(t_execs *exec, int err, t_execcmd *cmds)
{
	char		**args;

	if (!exec->cmd || !((t_execcmd *)exec->cmd)->args)
		return (0);
	args = cmds->args;
	if (!isbuiltin(args[0]))
		err = ft_exec2(exec, args, err, cmds);
	else
		err = builtin(exec);
	if (g_bigsignal == SIGINT)
		err = 130;
	return (signals(), err);
}
