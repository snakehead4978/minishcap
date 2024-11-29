/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:20:13 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/29 21:19:44 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_and(t_execs *exec, int err, t_andcmd *cmds)
{
	if (!exec->cmd)
		return (0);
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

int	ft_or(t_execs *exec, int err, t_orcmd *cmds)
{
	if (!exec->cmd)
		return (0);
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

static void	ft_sub2(t_execs *exec, t_shell *shell, char *buff, t_sub *cmds)
{
	int	err;

	if (ft_expandcmd(exec, cmds->cmd))
		exit_execfree(exec, 1);
	err = ft_sorter(exec, cmds->cmd);
	if (err != 1)
		execfree(exec);
	arrayfree(&shell->env);
	free(buff);
	free(shell);
	exit(err);
}

int	ft_sub(t_execs *exec, int err, t_sub *cmds)
{
	int	pid;

	if (!exec->cmd)
		return (0);
	pid = fork();
	if (!pid)
		ft_sub2(exec, exec->shell, exec->buff, cmds);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &err, 0);
		signals();
	}
	if (err == 1)
		err = 333;
	return (err);
}
