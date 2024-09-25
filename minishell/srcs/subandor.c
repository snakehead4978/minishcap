/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:20:13 by jla-chon          #+#    #+#             */
/*   Updated: 2024/09/25 20:51:59 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_and(t_execs *exec)
{
	t_andcmd	*cmds;
	int	err;

	if (!exec->cmd)
		return (seterr(exec, 0));
	cmds = (t_andcmd *)exec->cmd;
	err = ft_sorter(exec, cmds->left);
	if (!err)
		err = ft_sorter(exec, cmds->right);
	return (err);
}

int	ft_or(t_execs *exec)
{
	t_orcmd	*cmds;
	int	err;

	if (!exec->cmd)
		return (seterr(exec, 0));
	cmds = (t_orcmd *)exec->cmd;
	err = ft_sorter(exec, cmds->left);
	if (err)
		err = ft_sorter(exec, cmds->right);
	return (err);
}

int	ft_sub(t_execs *exec)
{	
	t_sub	*cmds;
	int	pid;
	int	err;

	if (!exec->cmd)
		return (seterr(exec, 0));
	cmds = (t_sub *)exec->cmd;
	pid = fork();
	err = ft_expandcmd(exec, cmds->cmd);
	if (!pid)
		err = ft_sorter(exec, cmds->cmd);
	else
		waitpid(pid, &err);
	return (err);
}
