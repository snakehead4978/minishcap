/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:28:34 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/01 22:16:14 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_execcfree(t_execs *exec)
{
	t_execcmd	*cmd;

	cmd = exec->cmd;
	arrayfree(cmd->args);
	return (0);
}

static int	ft_solo(t_execs *exec)
{
	t_cmd	*cmd;
	t_cmd	*down;

	cmd = exec->cmd;
	if (cmd->type == REDIR)
		down = ((t_redircmd *)cmd)->cmd;	
	else if (cmd->type == HERE)
		down = ((t_herecmd *)cmd)->cmd;	
	else
		down = ((t_sub *)cmd)->cmd;
	ft_sorterfree(exec, down);
	return (0);
}

static int	ft_branch(t_execs *exec)
{
	t_cmd	*cmd;
	t_cmd	*left;
	t_cmd	*right;

	cmd = exec->cmd;
	if (cmd->type == AND)
	{
		left = ((t_andcmd *)cmd)->left;
		right = ((t_andcmd *)cmd)->left;
	}
	else if (cmd->type == OR)
	{
		left = ((t_orcmd *)cmd)->left;
		right = ((t_orcmd *)cmd)->left;
	}
	else
	{
		left = ((t_pipecmd *)cmd)->left;
		right = ((t_pipecmd *)cmd)->left;
	}
	ft_sorterfree(exec, left);
	ft_sorterfree(exec, right);
}

static int	ft_sorterfree(t_execs *exec, t_cmd *cmd)
{
	exec->cmd = cmd;
	if (!cmd)
		return (0);
	if (cmd->type == EXEC)
		ft_execcfree(exec);
	else if (cmd->type == SUB || cmd->type == REDIR || cmd->type == HERE)
		ft_solo(exec);
	else if (cmd->type == PIPE || cmd->type == AND || cmd->type == OR)
		ft_branch(exec);
	return (0);
}

int	execfree(t_execs *exec)
{
	int	err;
	
	if (!exec)
		return (0);
	err = exec->ret;
	ft_sorterfree(exec, exec->shell->tree);
	ft_listfree(&exec->fds, fdsfree);
	// free all heredocs
	free(exec);
	return (0);
}
