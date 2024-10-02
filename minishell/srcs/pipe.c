/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:11:04 by snek              #+#    #+#             */
/*   Updated: 2024/10/01 22:14:51 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_execs *exec)
{
	t_pipecmd	*cmds;
	int	pid;
	int	fd[2];
	t_list	*fds;
	t_fds	*tmp;

	if (!exec->cmd)
		return (seterr(exec, 0));
	cmds = (t_pipecmd *)cmds;
	pipe(fd);
	fds = listnew(fdsnew(0, 0), fdsfree);
	tmp = fds->data;
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		tmp->fd = fd[1];
		tmp->type= FD_FILEOUT;
		if (!listaddback(&exec->fds, fds, fdsfree))
			return (execfree(exec), 1);
		if (ft_expandcmd(exec, cmds->left))
			return (execfree(exec), 1);
		exec->ret = ft_sorter(exec, cmds->left);
	}
	else
	{
		close(fd[1]);
		tmp->fd = fd[0];
		tmp->type= FD_FILEIN;
		if (!listaddback(&exec->fds, fds, fdsfree))
			return (execfree(exec), 1);
		if (ft_expandcmd(exec, cmds->right))
			return (execfree(exec));
		exec->ret = ft_sorter(exec, cmds->right);
	}
	ft_removefd(fds);
	return (exec->ret);
}
