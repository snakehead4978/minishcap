/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:48:08 by snek              #+#    #+#             */
/*   Updated: 2024/11/24 21:48:38 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!command->args || !command->args[0])
			return (1);
	}
	return (0);
}

int	executer(t_shell *shell, int err, char *buff)
{
	t_execs	*exec;

	if (!shell || !shell->tree)
		return (err);
	exec = ft_calloc(sizeof(t_execs), 1);
	exec->shell = shell;
	exec->fds = 0;
	exec->ret = err;
	exec->buff = buff;
	exec->stdcopies[0] = dup(0);
	exec->stdcopies[1] = dup(1);
	err = ft_expandcmd(exec, shell->tree);
	if (err)
		return (execfree(exec), err);
	err = ft_sorter(exec, exec->shell->tree);
	if (err != 1)
		execfree(exec);
	return (err);
}
