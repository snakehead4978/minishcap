/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:20:13 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/20 16:59:29 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_and(t_execs *exec)
{
	t_andcmd	*cmds;
	int	err;

	if (!exec->cmd)
		return (0);
	cmds = (t_andcmd *)exec->cmd;
	if (ft_expandcmd(exec, cmds->left))
		return (execfree(exec), 1);
	err = ft_sorter(exec, cmds->left);
	if (!err)
	{
		if (ft_expandcmd(exec, cmds->right))
			return (execfree(exec), 1);
		err = ft_sorter(exec, cmds->right);
	}
	return (err);
}

int	ft_or(t_execs *exec)
{
	t_orcmd	*cmds;
	int	err;

	if (!exec->cmd)
		return (0);
	cmds = (t_orcmd *)exec->cmd;
	if (ft_expandcmd(exec, cmds->left))
		return (execfree(exec), 1);
	err = ft_sorter(exec, cmds->left);
	if (err != 0 && err != 1)
	{
		if (ft_expandcmd(exec, cmds->right))
			return (execfree(exec), 1);
		err = ft_sorter(exec, cmds->right);
	}
	return (err);
}

int	ft_sub(t_execs *exec)
{	
	t_sub	*cmds;
	int	pid;
	int	err;
	t_shell	*shell;
	char	*buff;

	if (!exec->cmd)
		return (0);
	cmds = (t_sub *)exec->cmd;
	pid = fork();
	if (!pid)
	{
		shell = exec->shell;
		buff = exec->buff;
		if (ft_expandcmd(exec, cmds->cmd))
			exit_execfree(exec, 1);
		err = ft_sorter(exec, cmds->cmd);
		if (err != 1)
			execfree(exec);
		arrayfree(shell->env);
		free(buff);
		free(shell);
		exit(err);
	}
	else
		waitpid(pid, &err, 0);
	if (err == 1)
		err = 333;
	return (err);
}
