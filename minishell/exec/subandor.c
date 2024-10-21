/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:20:13 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/21 03:22:08 by snek             ###   ########.fr       */
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
	err = ft_expandcmd(exec, cmds->left);
	if (err)
		return (err);
	err = ft_sorter(exec, cmds->left);
	if (!err)
	{
		err = ft_expandcmd(exec, cmds->right);
		if (err)
			return (err);		
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
	err = ft_expandcmd(exec, cmds->left);
	if (err)
		return (err);
	err = ft_sorter(exec, cmds->left);
	if (err != 0 && err != 1)
	{
		err = ft_expandcmd(exec, cmds->right);
		if (err)
			return (err);		
		err = ft_sorter(exec, cmds->right);
	}
	return (err);
}

int	ft_sub(t_execs *exec)
{	
	t_sub	*cmds;
	int	pid;
	int	err;

	if (!exec->cmd)
		return (0);
	cmds = (t_sub *)exec->cmd;
	pid = fork();
	if (!pid)
	{
		err = ft_expandcmd(exec, cmds->cmd);
		if (err)
			exit(err);
		err = ft_sorter(exec, cmds->cmd);
		if (err != 1)
			execfree(exec);
		exit(err);
	}
	else
		waitpid(pid, &err, 0);
	if (err == 1)
		err = 333;
	return (err);
}
